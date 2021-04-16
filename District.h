#pragma once

#include <iostream>
#include <fstream>

using namespace std;
namespace elc {
    class District {
    private:
        int numOfElectors;
        int numOfTotalVoters; // total citizens that can vote
        int numOfVoters; // actual voters
        int id;
    protected:
        string name;
    public:
        //constructor
        District(); // File will init district
        District(const string &district_name, const int numOfElectors, const int numOfDistricts);
        District(const District &other) = default;  //default Copy Constructor
        virtual ~District() = default;
        //getters
        virtual string &getName() { return name; }
        int getTotalVoters() const { return numOfTotalVoters; }// return total num of citizen that can vote
        int getVoters() const { return numOfVoters; } // return number of citizen that vote
        int getNumOfElectors() const { return numOfElectors; }
        int getId() const { return id; }
        //setters
        void addTotalVoters();// counts the total citizens that can vote
        void addVoter();// counts the number of actual voters in the district
        //operators:
        District &operator=(const District &other) = default; //default operator=
        int operator()() const { return this->getId(); } //!IMPORTANT: implemented as the 'key' for 'my_find' algorithm!
        //prints
        friend std::ostream &operator<<(std::ostream &os, District &district);
        virtual void print_is_div() const;
        // File functions
        virtual void save(ostream &out) const;
        virtual void load(istream &in);
    };
}
