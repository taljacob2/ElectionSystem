#pragma once

#include "Party.h"
#include "District.h"
#include "DividedDistrict.h"
#include "DynamicArray.h"
#include <string>
#include "my_algorithms.h"

using namespace std;

namespace elc {
    int static constexpr DIVIDEDDISTRICT = 1;
    int static constexpr DISTRICT = 0;

    class Country {
    private:
        string name;
        int numOfParties;
        int numOfCitizens;
        int numOfDistricts;
        int numOfTotalElectors;
        DynamicArray<District *> districts;// Array of pointers to all districts in the country
        DynamicArray<Party *> parties;// Array of all pointers to all parties in the country
        DynamicArray<Citizen *> citizens;// Array of pointers to all citizens in the country

        //private function for managing country
        int calcDistrictWinnerParty(int **electorChart, int districtId) const; // calc which district belong to which party
        static int getMax(int *arr, int n, int &electorsNum); // return max in the array and replace max to -1
        static int getMax(const double *arr, int n); // return the index of max in the array
        void fillElectorChart(int **electorChart); // fill elector chart with votes
        void printElectorChart(int **electorChart);// print the electors for each district and their vote percentages:
        int **createElectorChart() const; /*CREATING ELECTORCHART: */ /*! DYNAMICALlY: !*/
        int *createElectorsWonArr_andPrintFinalResults();/*CREATE ELECTORSWONARR AND PRINT FINAL RESULTS:*/ /*! DYNAMICALlY: !*/

    public:

        // Constructors and Destructor
        Country(const string &nameOfCountry);
        ~Country();
        Country() = default; // for file load
        Country(const Country &other) = delete; // delete Copy Constructor

        //Getters functions
        int &getNumOfDistricts() { return numOfDistricts; }
        int getNumOfParties() const { return numOfParties; }
        int getNumOfCitizens() const { return numOfCitizens; }
        int getNumOfTotalElectors() const { return numOfTotalElectors; }
        DynamicArray<Citizen *> &getCitizens() { return citizens; };
        const string &getName() { return name; }
        DynamicArray<District * >&getDistricts(){return districts;}
        //Arrays functions
        void pushParty(const string &party_name, const int prime_id); // add party to parties array
        void pushDistrict(const string &district_name, const int numOfElectors, const int districtType); // add District to Districts array
        void pushCitizen(const string &citizen_name, const int id, const int yearOfBirth, const int districtId); // add Citizen to citizens array
        void addElector(const int citizen_id, const int party_id, const int district_id);// add citizen as elector in the district inside the party
        void addVote(const int citizen_id, const int party_id); // add to the party a vote return false if citizen/party/district don't exists.

        //Print functions
        void printParties(); //prints all parties
        void printDistricts(); //prints all districts
        void printCitizens(); //prints all citizens
        void printStatus(); //print election status

        //Operators
        Country &operator=(const Country &other) = delete;// delete operator=

        //File functions
        void save(ostream &out) const;
        void load(istream &in);
    };
}
