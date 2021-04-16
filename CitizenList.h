#pragma once

#include <iostream>
#include "Citizen.h"
#include <cstring>
#include "DynamicArray.h"
#include <list>
#include "my_algorithms.h"

namespace elc {
    class CitizenList {
        struct ListNode {
            ListNode(Citizen *ctzn); //constructor
            Citizen *citizen;
        };

        list<ListNode *> lst;
        int votesCounter;
    public:
        //constructor
        CitizenList();
        ~CitizenList();
        CitizenList(const CitizenList &other) { *this = other; }   //operator= implementation
        //setters
        void addVote(); // add vote to the party in this district
        void pushToList(Citizen *citizen); //return false if citizen already in the list
        //getters
        int getVoters() const { return votesCounter; }// return how many citizen voted for the party in this district
        int getListSize() const { return lst.size(); }
        //operators:
        CitizenList &operator=(const CitizenList &other) = default; //local variables are copied correctly, and 'lst' is deep copied thanks to STL operator=
        //prints
        bool printList(int n = -1, std::ostream &os = std::cout) const; //prints the first 'n' cells in the list --- (also compatible with different ostreams)
        friend std::ostream &operator<<(std::ostream &os, CitizenList const &citlst);//unused in this project
        //File functions
        void save(ostream &out) const;
        void load(istream &in);
    };
}
