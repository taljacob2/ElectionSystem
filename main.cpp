#include <iostream>
#include "addonfunctions.h"


int main() {
    int input;
    bool flag = true;

    Election *election = createElection();


    while (flag) {
        system("cls");
        printStatus(*election);
        printMenu();
        cin >> input;
        while ((input < Input::zero) || (input > Input::eleven)) {
            cout << "Number must be between " << Input::zero << "-" << Input::eleven << endl;
            cout << "Try again..." << endl;
            cin >> input;
        }
        switch (input) {
            case (Input::one)://insertDistrict
                insertDistrict(*election);
                break;
            case (Input::two)://insertCitizen
                insertCitizen(*election);
                break;
            case (Input::three)://insertParty
                insertParty(*election);
                break;
            case (Input::four)://insertElector
                insertElector(*election);
                break;
            case (Input::five)://printDistricts
                election->country.printDistricts();
                pressChar();
                break;
            case (Input::six)://printCitizens
                cout << "Printing all citizens:" << endl;
                election->country.printCitizens();
                pressChar();
                break;
            case (Input::seven)://printParties
                cout << "Printing all Parties:" << endl;
                election->country.printParties();
                pressChar();
                break;
            case (Input::eight)://VOTE
                addVote(*election);
                break;
            case (Input::nine)://printStatus
                try {
                    election->country.printStatus();
                }
                catch (exception &ex) {
                    cout << "ERROR. " << ex.what() << endl;
                }
                pressChar();
                break;
            case (Input::ten)://Save
                saveElection(*election);
                break;
            case (Input::eleven)://Load
                delete election;
                electionLoad(&election);
                break;
            case (Input::zero)://Exit
                flag = false;
                break;
        }
    }
    cout << "Goodbye :)" << endl;
    delete election;

    return 0;
}
