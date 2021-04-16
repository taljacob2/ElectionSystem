#pragma once

#include <string>
#include "District.h"
#include "DynamicArray.h"
using namespace std;
namespace elc {

    class Citizen {
    private:
        string name;
        int id;
        int yearOfBirth;
        District *citizen_district;
        bool voted;
        bool prime;
        bool elector;
    public:
        //constructor
        Citizen(const string &citizen_name, const int id, const int yearOfBirth, const District *citizen_district);
        Citizen(const Citizen &other) = default;  //default Copy Constructor
        Citizen() = default; // For File to load citizens start with garbage.
        //getters
        int getId() const { return id; }
        const string &getName() { return name; }
        bool getVoted() const { return voted; }
        District *getDistrict() const { return citizen_district; }
        bool isElector() const { return elector; } // return true if citizen is already elector
        bool isPrime() const { return prime; } // return true if citizen prime else false
        //setters
        void setPrime(); // Set prime to true
        void setElector();// set elector to true
        void setVoted(); // set citizen voted to true

        //operators:
        Citizen &operator=(const Citizen &other) = default; //default operator=
        int operator()() const { return this->getId(); } //!IMPORTANT: implemented as the 'key' for 'my_find' algorithm!
        //prints
        friend std::ostream &operator<<(std::ostream &os, Citizen const &citizen); // print citizen
        //File functions
        void save(ostream &out) const;
        void load(istream &in);
    };
}
