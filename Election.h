#pragma once

#include <iostream>
#include <fstream>
#include "Country.h"
#include "LoaderHelper.h"

using namespace std;
namespace elc {
    class Election {
    private:
        int year, month, day;
        bool regularElection;
    public:
        Country country;

    public:
        Election(const int year, const int month, const int day, const string &nameOfCountry, const bool regularElection, const int electors = 0);
        Election(const Election &other) = delete; // delete Copy Constructor
        Election &operator=(const Election &other) = delete;  // delete operator=
        Country &get_country() { return country; } //important
        int getMonth() const { return month; }
        int getYear() const { return year; }
        int getDay() const { return day; }
        bool isRegularElection() const { return regularElection; }

        //File functions
        void load(istream &in);
        void save(ostream &out) const;
        Election(istream &in); //Ctor from file
    };
}

