
#include "District.h"

namespace elc {
    //constructor
    District::District() : numOfElectors(0), numOfTotalVoters(0), numOfVoters(0), id(0) {}
    District::District(const string &district_name, const int numOfElectors, const int numOfDistricts) : District() {
        this->name = district_name;
        this->numOfElectors = numOfElectors;
        this->id = numOfDistricts;
    }
    //setters
    void District::addVoter() {// counts the number of actual voters in the district
        numOfVoters++;
    }
    void District::addTotalVoters() {// counts the total citizens that can vote
        numOfTotalVoters++;
    }
    //prints
    std::ostream &operator<<(std::ostream &os, District &district) {
        os << "District ID = " << district.id << " | ";
        os << "District Name = " << district.name << " | ";
        os << "Number of electors = " << district.numOfElectors << " | ";
        district.print_is_div();
        os << std::endl;
        return os;
    }
    void District::print_is_div() const {
        std::cout << "Unified";
    }
    //File functions
    void District::save(ostream &out) const {
        int len = name.size();
        out.write(reinterpret_cast<const char *>(&len), sizeof(len));
        out.write(reinterpret_cast<const char *>(name.c_str()), sizeof(char) * len);
        out.write(reinterpret_cast<const char *>(&numOfElectors), sizeof(numOfElectors));
        out.write(reinterpret_cast<const char *>(&numOfTotalVoters), sizeof(numOfTotalVoters));
        out.write(reinterpret_cast<const char *>(&numOfVoters), sizeof(numOfVoters));
        out.write(reinterpret_cast<const char *>(&id), sizeof(id));
        if (!out.good())
            throw (runtime_error("District save failed."));
    }
    void District::load(istream &in) {
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
        in.read(reinterpret_cast<char *>(&numOfElectors), sizeof(numOfElectors));
        in.read(reinterpret_cast<char *>(&numOfTotalVoters), sizeof(numOfTotalVoters));
        in.read(reinterpret_cast<char *>(&numOfVoters), sizeof(numOfVoters));
        in.read(reinterpret_cast<char *>(&id), sizeof(id));
        if (!in.good())
            throw (runtime_error("District load failed."));
    }
}
