
#include "Election.h"

namespace elc {
    Election::Election(int _year, int _month, int _day, const string &nameOfCountry, const bool regularElection, const int electors) :
            year(_year), month(_month), day(_day), regularElection(regularElection), country(nameOfCountry) {
        if (!regularElection) //only if this is a Simple Election:
            country.pushDistrict("Default", electors, DIVIDEDDISTRICT);
        elc::LoaderHelper::country =&country; //Singleton
    }
    void Election::load(istream &in) {
        in.read(reinterpret_cast<char *>(&this->year), sizeof(this->year));
        in.read(reinterpret_cast<char *>(&this->month), sizeof(this->year));
        in.read(reinterpret_cast<char *>(&this->day), sizeof(this->year));
        in.read(reinterpret_cast<char *>(&this->regularElection), sizeof(this->regularElection));
        if (!in.good())
            throw (runtime_error("Election load failed"));
        country.load(in);
    }
    void Election::save(ostream &out) const {
        out.write(reinterpret_cast<const char *>(&year), sizeof(year));
        out.write(reinterpret_cast<const char *>(&month), sizeof(month));
        out.write(reinterpret_cast<const char *>(&day), sizeof(day));
        out.write(reinterpret_cast<const char *>(&regularElection), sizeof(regularElection));
        if (!out.good())
            throw (runtime_error("Election save failed"));
        country.save(out);
    }
    Election::Election(istream &in) {
        elc::LoaderHelper::country =&country; //Singleton
        load(in);
    }
}
