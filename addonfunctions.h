#pragma once

#include "Election.h"

#include <iostream>
#include <ctime>
// ALL MAIN FUNCTIONS
using namespace elc;
using namespace std;

class Input {
public:
    constexpr static int zero = 0;
    constexpr static int one = 1;
    constexpr static int two = 2;
    constexpr static int three = 3;
    constexpr static int four = 4;
    constexpr static int five = 5;
    constexpr static int six = 6;
    constexpr static int seven = 7;
    constexpr static int eight = 8;
    constexpr static int nine = 9;
    constexpr static int ten = 10;
    constexpr static int eleven = 11;
};

void insertDistrict(Election &elc);
void printStatus(Election &elc);
void insertParty(Election &elc);
void insertCitizen(Election &elc);
void pressChar();
void insertElector(Election &elc);
void addVote(Election &elc);
void getDate(int &day, int &month, int &year); // return current date of the user computer
void printMenu(); // prints the Main Menu interface
void saveElection(Election &elc);
void electionLoad(Election **elc);
void printSelectElectionMenu();
void printStartNewElectionMenu();
Election *startNewElection(int year, int month, int day);
Election *createElection();
