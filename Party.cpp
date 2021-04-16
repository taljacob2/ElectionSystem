
#include "Party.h"
#include "LoaderHelper.h"

namespace elc {
    //Constructor
    Party::Party() : prime(nullptr), numOfDistricts(nullptr), id(0), totalvotes(0), totalElectors(0) {}
    Party::Party(const Party &other) { // Copy Constructor
        *this = other; // using deep copy operator= defined
    }
    Party::~Party() {
        for (auto e:electors)
            delete e;
    }
    Party::Party(const string &party_name, const Citizen *prime, const int *numOfDistricts, const int numOfParties) : Party() // Ctor party with given data
    {
        name = party_name;
        this->prime = const_cast<Citizen *>(prime);
        this->numOfDistricts = const_cast<int *>(numOfDistricts);
        this->id = numOfParties;
        updateElectorsArray();
    }

    //Methods
    void Party::setNumOfDistricts(const int *numOfDistricts) // set numOfDistricts to point to given pointer
    {
        this->numOfDistricts = const_cast<int *>(numOfDistricts);
    }
    void Party::setPrime(Citizen *_prime) {// set Party prime to given prime pointer
        this->prime = _prime;
    }
    std::ostream &operator<<(std::ostream &os, const Party &party) {
        std::cout << "Party ID = " << party.id << " | ";
        std::cout << "Party Name = " << party.name << std::endl;
        std::cout << "Party Prime = " << *party.prime << std::endl;
        for (int i = 0; i < *party.numOfDistricts; i++) {
            std::cout << "Electors List of District " << i << ": {" << std::endl;
            party.electors[i]->printList();
            std::cout << "}" << std::endl;
        }
        std::cout << "----------------------" << std::endl;
        return os;
    }
    void Party::pushElector(const Citizen *elector, const int district_id) // add elector to electors array in specific district. return false if elector alreay in the list
    {
        electors[district_id]->pushToList(const_cast<Citizen *>(elector));
    }
    void Party::addVote(const Citizen &citizen) // Add citizen vote
    {
        totalvotes++;
        return electors[citizen.getDistrict()->getId()]->addVote();
    }
    Party &Party::operator=(const Party &other) {
        if (this != &other) {
            this->name = other.name;
            this->prime = other.prime;
            this->numOfDistricts = other.numOfDistricts;
            electors = other.electors;
            id = other.id;
            this->totalvotes = other.totalvotes;
            this->totalElectors = other.totalElectors;
        }
        return *this;
    }
    void Party::updateElectorsArray() { // updates the Electors Array
        while (electors.size() < *numOfDistricts) {
            electors.push_back(new CitizenList());
        }
    }
    void Party::addWinnerElectorsNumber(const int numToadd) { // add how much electors the party won in this district
        totalElectors += numToadd;
    }
    void Party::resetWinnerElectorsNumber() {//resets totalElectors counter to 0. used to enable another election calculation
        totalElectors = 0;
    }
    void Party::PrintPercentOfVotes(int districtId, int voters) {//prints the percent of votes for a specific Party in a specific District
        double sum;
        if (voters == 0)
            sum = 0;
        else
            sum = static_cast<double>(electors[districtId]->getVoters()) / voters;
        std::cout << name << " got: " << electors[districtId]->getVoters() << " votes and won " << sum * 100 << "% of the votes" << std::endl;
    }
    void Party::printElectors(const int n, const int districtId) // print n electors from district ID
    {
        if ((n <= electors[districtId]->getListSize()) && (n != 0))
            std::cout << "Electors of party " << name << ": " << std::endl;
        if (!electors[districtId]->printList(n)) {
            std::cout << "ERROR: Not enough electors inserted in party " << name << ". Only " << electors[districtId]->getListSize() << " electors added. need at least " << n << " electors." << std::endl;
        }
    }
    //File functions
    void Party::save(ostream &out) const {
        int primeId = prime->getId();
        int len = name.size();
        out.write(reinterpret_cast<const char *>(&len), sizeof(len));
        out.write(reinterpret_cast<const char *>(name.c_str()), sizeof(char) * len);
        out.write(reinterpret_cast<const char *>(&id), sizeof(id));
        out.write(reinterpret_cast<const char *>(&totalvotes), sizeof(totalvotes));
        out.write(reinterpret_cast<const char *>(&totalElectors), sizeof(totalElectors));
        out.write(reinterpret_cast<const char *>(&primeId), sizeof(primeId));// on load connect prime by this id
        //on load we made sure to set numOfDistricts beforehand:
        for (int i = 0; i < *numOfDistricts; i++) {
            try {
                electors[i]->save(out);//this saves locals variables of the list and then all the IDs for each citizen in the list
            }
            catch (...) {
                throw;
            }
        }

        if (!out.good())
            throw (runtime_error("Party save failed"));
    }
    void Party::load(istream &in) {
        int primeId;
        int len;
        in.read(reinterpret_cast<char *>(&len), sizeof(len));
        char *tmp;
        try {
            tmp = new char[len + 1];
        }
        catch (const std::bad_alloc &) {
            throw (runtime_error("Country name load failed."));
        }
        in.read(reinterpret_cast<char *>(tmp), sizeof(char) * len);
        tmp[len] = '\0';
        name = tmp;
        delete[]tmp;

        in.read(reinterpret_cast<char *>(&id), sizeof(id));
        in.read(reinterpret_cast<char *>(&totalvotes), sizeof(totalvotes));
        in.read(reinterpret_cast<char *>(&totalElectors), sizeof(totalElectors));
        //FOR PARTY *prime:
        //Connect *prime by the primeId: with the find function:
        in.read(reinterpret_cast<char *>(&primeId), sizeof(primeId));
        auto _prime = my_find<DynamicArray<elc::Citizen *> &, elc::Citizen *, int>(elc::LoaderHelper::getInstance()->getCitizens(), primeId);//return pointer to citizen if found. else return nullptr
        setPrime(_prime);

        for (auto e:electors)// resetting the array
            delete e;
        electors.clear();

        while (electors.size() < *numOfDistricts)//for each District
            electors.push_back(new CitizenList());//set this array to have a new dynamically uninitialized CitizenList

        for (int i = 0; i < *numOfDistricts; i++) {//for each CitizenList:
            try {
                electors[i]->load(in);// sets the local variables of the CitizenList + loads the 'lst' as following: for each each citizenID, it finds the correct pointer to it and connects it to the list
            }
            catch (...) {
                throw;
            }
        }

        if (!in.good())
            throw (runtime_error("Party load failed."));
    }
}
