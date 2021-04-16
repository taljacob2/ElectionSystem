#pragma once

#include <exception>

//GENERAL FIND ALGORITHM:
template<typename DB, typename POINTER, typename KEY>
POINTER my_find(DB db, KEY key) {
    /* !MUST IMPLEMENT 'operator() = return 'key'' IN THE DATABASE CELL! */
    /* this generic function searches for a key in a database, and returns a pointer to it */
    for (auto &i : db) {
        if ((*i)() == key)
            return i;
    }
    return nullptr; //if didn't find, return 'nullptr'
}
