#pragma once

#include "CitizenList.h"
#include "Citizen.h"
#include <cmath>
#include "DynamicArray.h"


namespace elc {

    class Party {
    private:
        string name;
        Citizen *prime;
        int *numOfDistricts;
        int id;
        int totalvotes;
        int totalElectors;
        DynamicArray<CitizenList *> electors;
    public:
        // Constructor
        Party(); // For file to fill after read file
        Party(const Party &other); // Copy Constructor
        Party(const string &party_name, const Citizen *prime, const int *numOfDistricts, const int numOfParties); // Ctor party with given data
        ~Party();
        //operators:
        Party &operator=(const Party &other);
        //getters
        int getTotalVotes() const { return totalvotes; }
        const string &getName() const { return name; }
        const string &getPrimeName() { return prime->getName(); }
        DynamicArray<CitizenList *> &getElectorsArray() { return electors; }
        int numOfVotesForDistrict(int districtId) { return electors[districtId]->getVoters(); }; // return the votes for the district id
        int getWinnerElectorsNumber() const { return totalElectors; }
        //setters
        void pushElector(const Citizen *elector, const int district_id); // add elector to electors array in specific district. return false if elector alreay in the list
        void addVote(const Citizen &citizen); // Add citizen vote
        void updateElectorsArray();// updates the Electors Array
        void addWinnerElectorsNumber(const int numToadd); // add how much electors the party won in this district
        void resetWinnerElectorsNumber(); //resets totalElectors counter to 0. used to enable another election calculation
        void setNumOfDistricts(const int *numOfDistricts); // set numOfDistricts to point to given pointer
        void setPrime(Citizen *_prime);// set Party prime to given prime pointer
        //prints
        void PrintPercentOfVotes(const int districtId, const int voters); //prints the percent of votes for a specific Party in a specific District
        void printElectors(const int n, const int districtId); // print n electors from district ID
        friend std::ostream &operator<<(std::ostream &os, const Party &party); // Print Party using std
        //File functions
        void save(ostream &out) const;
        void load(istream &in);
    };
}
