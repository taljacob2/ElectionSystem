
#include "Citizen.h"
#include "LoaderHelper.h"
namespace elc {
    //constructor
    Citizen::Citizen(const string &citizen_name, const int id, const int yearOfBirth, const District *citizen_district) {
        name = citizen_name;
        this->id = id;
        this->yearOfBirth = yearOfBirth;
        this->citizen_district = const_cast<District *>(citizen_district);
        voted = false;
        prime = false;
        elector = false;
    }
    //setters
    void Citizen::setPrime() { // Set prime to true
        prime = true;
    }
    void Citizen::setElector() { // set elector to true
        elector = true;

    }
    void Citizen::setVoted() {// set citizen voted to true
        voted = true;
    }

    //prints
    std::ostream &operator<<(std::ostream &os, Citizen const &citizen) {
        os << "Name = " << citizen.name << ";   "
           << "ID = " << citizen.id << ";   "
           << "YearOfBirth = " << citizen.yearOfBirth << ";   "
           << "District_id = " << citizen.citizen_district->getId() << ";   "
           << "District name = " << (citizen.citizen_district->getName()) << ";    "
           << "Did vote? = " << (citizen.voted ? "yes" : "no") << std::endl;

        return os;
    }
    //File functions
    void Citizen::save(ostream &out) const {
        int len = name.size();
        out.write(reinterpret_cast<const char *>(&len), sizeof(len));
        out.write(reinterpret_cast<const char *>(name.c_str()), sizeof(char) * len);
        out.write(reinterpret_cast<const char *>(&id), sizeof(id));
        out.write(reinterpret_cast<const char *>(&yearOfBirth), sizeof(yearOfBirth));
        out.write(reinterpret_cast<const char *>(&voted), sizeof(voted));
        out.write(reinterpret_cast<const char *>(&prime), sizeof(prime));
        out.write(reinterpret_cast<const char *>(&elector), sizeof(elector));
        //We will remember to connect citizen_district in the Country.load method --- by finding the correct pointer to this district thanks to the 'citizen_district_id' key
        int citizen_district_id = citizen_district->getId();
        out.write(reinterpret_cast<const char *>(&citizen_district_id), sizeof(citizen_district_id));/*!MUST BE THE LAST (OR THE FIRST) in this load, so we could read the 'citizen_district_id' in Country.load!*/
        if (!out.good())
            throw (runtime_error("Citizen save failed"));
    }

    void Citizen::load(istream &in) {
        int len;
        in.read(reinterpret_cast<char *>(&len), sizeof(len));
        char *tmp;
        try {
            tmp = new char[len + 1];
        }
        catch (const std::bad_alloc &) {
            throw (runtime_error("Citizen name load failed."));
        }
        in.read(reinterpret_cast<char *>(tmp), sizeof(char) * len);
        tmp[len] = '\0';
        name = tmp;
        delete[]tmp;
        in.read(reinterpret_cast<char *>(&id), sizeof(id));
        in.read(reinterpret_cast<char *>(&yearOfBirth), sizeof(yearOfBirth));
        in.read(reinterpret_cast<char *>(&voted), sizeof(voted));
        in.read(reinterpret_cast<char *>(&prime), sizeof(prime));
        in.read(reinterpret_cast<char *>(&elector), sizeof(elector));
        //CONNECTING citizen_district_id to district:
        int citizen_district_id;
        in.read(reinterpret_cast<char *>(&citizen_district_id), sizeof(citizen_district_id));
        citizen_district = my_find<DynamicArray<elc::District *> &, elc::District *, int>(elc::LoaderHelper::getInstance()->getDistricts(), citizen_district_id); //return pointer to district if found. else return nullptr

        if (!in.good())
            throw (runtime_error("Citizen load failed"));
    }
}
