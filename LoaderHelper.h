#pragma once

#include "Country.h"

namespace elc {
    class LoaderHelper {
    public:
        static Country *country;

        //Constructor:
        LoaderHelper() = default; //default Constructor
        LoaderHelper(const LoaderHelper &other) = delete; //delete CopyConstructor
        static Country *getInstance(){return country;}

    };
}