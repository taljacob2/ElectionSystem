#pragma once

#include "District.h"

namespace elc {
    class DividedDistrict : public District {
    public:
        DividedDistrict(const string &district_name, const int numOfElectors, const int numOfDistricts) : District(district_name, numOfElectors, numOfDistricts) {}
        DividedDistrict() = default; // File will init District
        void print_is_div() const override;
        string &getName() override { return name; }
    };
}
