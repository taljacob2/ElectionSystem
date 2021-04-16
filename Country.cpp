#include <typeinfo>
#include "Country.h"

namespace elc {

    //Constructors
    Country::Country(const string &nameOfCountry) : name(nameOfCountry), numOfParties(0), numOfCitizens(0), numOfDistricts(0), numOfTotalElectors(0) {}
    Country::~Country() {
        for (auto c:citizens)
            delete c;
        for (auto d: districts)
            delete d;
        for (auto p:parties)
            delete p;
    }

    //Arrays functions
    void Country::pushParty(const string &party_name, const int prime_id) // add party to parties array
    {
        auto prime = my_find<DynamicArray<elc::Citizen *> &, elc::Citizen
        *, int>(citizens, prime_id); //return pointer to citizen if found. else return nullptr
        if (prime == nullptr || prime->isPrime()) // if citizen not found or citizen already prime of the party
        {
            if (prime == nullptr)
                throw (runtime_error("Prime was not found."));
            else
                throw (runtime_error("Prime already prime"));
        }
        prime->setPrime();
        parties.push_back(new Party(party_name, prime, &numOfDistricts, numOfParties));

        numOfParties++;
    }
    void Country::pushDistrict(const string &district_name, const int numOfElectors, const int districtType) { // add district to districts array
        numOfTotalElectors += numOfElectors;
        if (districtType == DISTRICT) // type 0 is regular district
            districts.push_back(new District(district_name, numOfElectors, numOfDistricts));
        else if (districtType == DIVIDEDDISTRICT) // type 1 is divided district
            districts.push_back(new DividedDistrict(district_name, numOfElectors, numOfDistricts));
        numOfDistricts++;
        for (auto party : parties) {
            party->updateElectorsArray();
        }
    }
    void Country::pushCitizen(const string &citizen_name, const int id, const int yearOfBirth, const int districtId) // add Citizen to citizens array
    {
        Citizen *_tmp = my_find<DynamicArray<elc::Citizen *> &, elc::Citizen *, int>(citizens, id); //return pointer to citizen if found. else return nullptr
        if (_tmp != nullptr)
            throw (runtime_error("Citizen was not found."));

        auto citizen_district = my_find<DynamicArray<elc::District *> &, elc::District
        *, int>(districts, districtId); //return pointer to district if found. else return nullptr
        districts[districtId]->addTotalVoters();
        citizens.push_back(new Citizen(citizen_name, id, yearOfBirth, citizen_district));
        numOfCitizens++;
    }
    void Country::addElector(const int citizen_id, const int party_id, const int district_id)// add citizen as elector in the district inside the party
    {
        auto tmp = my_find<DynamicArray<elc::Citizen *> &, elc::Citizen
        *, int>(citizens, citizen_id); //return pointer to citizen if found. else return nullptr
        if (tmp == nullptr || tmp->isPrime() || tmp->isElector()) {
            if (tmp == nullptr)
                throw (runtime_error("Citizen was not found."));
            else if (tmp->isPrime())
                throw (runtime_error("Citizen already prime."));
            else
                throw (runtime_error("Citizen already elector."));
        }
        parties[party_id]->pushElector(tmp, district_id);
    }
    void Country::addVote(const int citizen_id, const int party_id) // add to the party a vote return false if citizen/party/district don't exists.
    {
        auto tmp = my_find<DynamicArray<elc::Citizen *> &, elc::Citizen
        *, int>(citizens, citizen_id); //return pointer to citizen if found. else return nullptr
        if (tmp == nullptr || tmp->getVoted()) {
            if (tmp == nullptr)
                throw (runtime_error("Citizen was not found."));
            else
                throw (runtime_error("Citizen already voted."));
        }
        parties[party_id]->addVote(*tmp);
        districts[tmp->getDistrict()->getId()]->addVoter();
        tmp->setVoted();
    }

    //Print functions
    void Country::printParties() {//prints all parties
        for (int i = 0; i < numOfParties; i++) {
            std::cout << *parties[i];
        }
    }
    void Country::printDistricts() {//prints all districts
        std::cout << "Printing districts:" << std::endl;
        int i = 0;
        for (auto d: districts) {
            std::cout << "District number: " << ++i << std::endl;
            std::cout << *d << std::endl;
        }
    }
    void Country::printCitizens() {//prints all citizens
        for (auto c: citizens) {
            std::cout << *c;
        }
    }
    void Country::printStatus() // print election status
    {
        //CHECK LEGALITY:
        if (numOfParties < 2) {
            throw (runtime_error("Need at least 2 parties."));
        }

        std::cout << std::endl << "**************************************" << std::endl;

        //CREATING ELECTORCHART:
        int **electorChart = createElectorChart();
        fillElectorChart(electorChart);

        //BEGIN PRINT:
        printElectorChart(electorChart);

        //CREATE ELECTORSWONARR AND PRINT FINAL RESULTS:
        int *electorswonArr = createElectorsWonArr_andPrintFinalResults();

        // DELETING AND RESETTING:
        for (int i = 0; i < numOfDistricts; i++)
            delete[]electorChart[i];
        delete[]electorswonArr;
        delete[]electorChart;
        for (int i = 0; i < numOfParties; i++)
            parties[i]->resetWinnerElectorsNumber();
    }

    // private functions
    void Country::fillElectorChart(int **electorChart) {
        for (int i = 0; i < numOfDistricts; i++) // fill the chart with electors
        {
            double numOfElectors; // the number of how much votes = elector
            numOfElectors = static_cast<double>(districts[i]->getVoters()) / districts[i]->getNumOfElectors();
            double *districtPartyVotes = new double[numOfParties]; //create temporary double array for calculation
            for (int j = 0; j < numOfParties; j++) // fill the district Party votes
            {
                districtPartyVotes[j] = parties[j]->numOfVotesForDistrict(i); // i is the district id
            }
            for (int j = 0; j < districts[i]->getNumOfElectors(); j++) {// each time, calculate for what party to give an elector. With the total of 'numofElectors' times:
                int index = getMax(districtPartyVotes, numOfParties);//get the party with the most votes
                electorChart[i][index]++; //give this party an elector
                districtPartyVotes[index] -= numOfElectors; //remove those votes from this party and get ready for another calculation.
            }
            delete[]districtPartyVotes; // We have finished the calculation. Delete the temporary double array that was made for calculation.
        }
    }
    int Country::getMax(int *arr, int n, int &electorsNum) // return max in the array and replace max to -1
    {
        int max = arr[0];
        int index = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] > max) {
                index = i;
                max = arr[i];
            }
        }
        electorsNum = arr[index];
        arr[index] = -1;
        return index;
    }
    int Country::getMax(const double *arr, int n) // return the index of max in the array
    {
        double max = arr[0];
        int index = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] > max) {
                index = i;
                max = arr[i];
            }
        }
        return index;
    }
    int Country::calcDistrictWinnerParty(int **electorChart, int districtId) const { //finds the Party that had won in the current district specified and returns the index of it
        int max = electorChart[districtId][0];
        int index = 0;
        for (int i = 1; i < numOfParties; i++) {
            if (electorChart[districtId][i] > max) {
                max = electorChart[districtId][i];
                index = i;
            }
        }
        return index;
    }
    void Country::printElectorChart(int **electorChart) { // print the electors for each district and their vote percentages:
        for (int i = 0; i < numOfDistricts; i++) // print all Districts election status
        {
            if (typeid(*(districts[i])) == typeid(District)) {
                int winner_party_id = calcDistrictWinnerParty(electorChart, i); // return the party winner in i= district
                std::cout << districts[i]->getName() << ": " << std::endl;
                std::cout << "Gives: " << districts[i]->getNumOfElectors() <<
                          " electors to: " << parties[winner_party_id]->getName() << " with prime: " << parties[winner_party_id]->getPrimeName() << std::endl;
                parties[winner_party_id]->addWinnerElectorsNumber(districts[i]->getNumOfElectors()); // add how much electors the party won in this district
            }
            else if (typeid(*districts[i]) == typeid(DividedDistrict)) // District is Divided District
            {
                if (districts[i]->getName() == "Default")
                    std::cout << "Simple Election: " << std::endl;
                else
                    std::cout << "Divided district " << districts[i]->getName() << ": " << std::endl;
                for (int j = 0; j < numOfParties; j++) // set Electors to each party the district gives
                {
                    parties[j]->addWinnerElectorsNumber(electorChart[i][j]);
                }
            }
            std::cout << "The electors: {" << std::endl;
            for (int j = 0; j < numOfParties; j++) //print electors list of the party
            {
                parties[j]->printElectors(electorChart[i][j], i); // i is the district of the party we want to print the electors
            }
            std::cout << "}" << std::endl;
            for (int j = 0; j < numOfParties; j++) // print how much votes the party got and percents
            {
                parties[j]->PrintPercentOfVotes(i, districts[i]->getVoters());
            }
            if (districts[i]->getTotalVoters() != 0)
                std::cout << "Total votes in this district: " << (static_cast<double>(districts[i]->getVoters()) / districts[i]->getTotalVoters()) * 100 << "%" << std::endl;
            else
                std::cout << "Total votes in this district: 0%" << std::endl;
            std::cout << "**************************************" << std::endl;
        }
    }
    int **Country::createElectorChart() const { /*CREATING ELECTORCHART: */ /*! DYNAMICALlY: !*/
        int **electorChart = new int *[numOfDistricts]; // elector chart represent in each cell how much electors for given (i,j)==(districtId,partyId)
        for (int i = 0; i < numOfDistricts; i++)
            electorChart[i] = new int[numOfParties];
        for (int i = 0; i < numOfDistricts; i++) // init electorChart
        {
            for (int j = 0; j < numOfParties; j++)
                electorChart[i][j] = 0;
        }
        return electorChart;
    }
    int *Country::createElectorsWonArr_andPrintFinalResults() { /*CREATE ELECTORSWONARR AND PRINT FINAL RESULTS:*/ /*! DYNAMICALlY: !*/
        int *electorswonArr = new int[numOfParties]; // array of electors won in each party
        for (int i = 0; i < numOfParties; i++) {
            electorswonArr[i] = parties[i]->getWinnerElectorsNumber(); // get how many electors the party got
        }
        for (int i = 0; i < numOfParties; i++) {
            int electorsNum;
            int party_index = getMax(electorswonArr, numOfParties, electorsNum);
            if (i == 0)
                std::cout << "\n**********THE WINNER PARTY************\n" << std::endl;
            std::cout << parties[party_index]->getName() << " with prime " << parties[party_index]->getPrimeName() << " won " << parties[party_index]->getWinnerElectorsNumber() << " Electors and got " << parties[party_index]->getTotalVotes()
                      << " Votes" << std::endl;

            if (i == 0)
                std::cout << "\n************************************\n" << std::endl;
        }
        return electorswonArr;
    }

    // File functions
    void Country::save(ostream &out) const {
        const char type_dividedDistrict = DIVIDEDDISTRICT;
        const char type_regularDistrict = DISTRICT;
        int len = name.size();
        out.write(reinterpret_cast<const char *>(&len), sizeof(len));
        out.write(reinterpret_cast<const char *>(name.c_str()), sizeof(char) * len);
        out.write(reinterpret_cast<const char *>(&numOfParties), sizeof(numOfParties));
        out.write(reinterpret_cast<const char *>(&numOfCitizens), sizeof(numOfCitizens));
        out.write(reinterpret_cast<const char *>(&numOfDistricts), sizeof(numOfDistricts));
        out.write(reinterpret_cast<const char *>(&numOfTotalElectors), sizeof(numOfTotalElectors));

        for (int i = 0; i < numOfDistricts; i++) {
            if (typeid(*districts[i]) == typeid(DividedDistrict)) // Save 1 for divided district
            {
                out.write(reinterpret_cast<const char *>(&type_dividedDistrict), sizeof(type_dividedDistrict));
            }
            else // save type 0 for regular district
            {
                out.write(reinterpret_cast<const char *>(&type_regularDistrict), sizeof(type_regularDistrict));
            }
            try {
                districts[i]->save(out);
            }
            catch (...) {
                throw;
            }
        }
        for (int i = 0; i < numOfCitizens; i++) {
            try {
                citizens[i]->save(out);
            }
            catch (...) {
                throw;
            }
        }
        for (int i = 0; i < numOfParties; i++) {
            try {
                parties[i]->save(out);
            }
            catch (...) {
                throw;
            }
        }
        if (!out.good())
            throw (runtime_error("Country save failed."));
    }
    void Country::load(istream &in) {
        int len;
        in.read(reinterpret_cast<char *>(&len), sizeof(len));
        char *tmp;
        try {
            tmp = new char[len + 1];
        }
        catch (const bad_alloc &) {
            throw (runtime_error("Country name load failed."));
        }
        in.read(reinterpret_cast<char *>(tmp), sizeof(char) * len);
        tmp[len] = '\0';
        name = tmp;
        delete[]tmp;
        // Checking success at the end in.good()
        in.read(reinterpret_cast<char *>(&this->numOfParties), sizeof(this->numOfParties));
        in.read(reinterpret_cast<char *>(&this->numOfCitizens), sizeof(this->numOfCitizens));
        in.read(reinterpret_cast<char *>(&this->numOfDistricts), sizeof(this->numOfDistricts));
        in.read(reinterpret_cast<char *>(&this->numOfTotalElectors), sizeof(this->numOfTotalElectors));

        char district_type;
        for (int i = 0; i < numOfDistricts; i++) {  // load districts
            in.read(reinterpret_cast<char *>(&district_type), sizeof(district_type));
            District *tmp = district_type == DIVIDEDDISTRICT ? new DividedDistrict() : new District();
            districts.push_back(tmp);
            try {
                districts[i]->load(in);
            }
            catch (...) {
                throw;
            }
        }

        for (int i = 0; i < numOfCitizens; i++) { /* load citizens*/ /*!Must load Citizens before Parties!*/
            int citizen_district_id;
            citizens.push_back(new Citizen());
            try {
                citizens[i]->load(in);

            }
            catch (...) {
                throw;
            }
        }

        for (int i = 0; i < numOfParties; i++) { // load parties
            int citizenId;// a key to find the correct Citizen* to insert into the list
            int primeId;// a key to find the correct Citizen* to insert into the party
            Citizen *citizen; //points to the citizen found by citizenId
            parties.push_back(new Party());
            parties[i]->setNumOfDistricts(&numOfDistricts);

            try {
                parties[i]->load(in);
            }
            catch (...) {
                throw;
            }
        }
        if (!in.good())
            throw (runtime_error("Country load failed."));
    }
}
