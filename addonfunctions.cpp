#define _CRT_SECURE_NO_WARNINGS // needed for 'time_t'

#include "addonfunctions.h"

void insertDistrict(Election &elc) {
    string name;
    int numOfElectors;
    int district_type;
    if (!elc.isRegularElection()) {
        cout << "Cannot add district in simple election." << endl;
        pressChar();
        return;
    }
    cout << "Enter the name of the district: ";
    cin.ignore(1, '\n'); //ignores one '\n'
    getline(cin, name);
    cout << "Enter the number of electors in this district: ";
    cin >> numOfElectors;
    while (numOfElectors <= 0) {
        cout << "Elector number must be greater than 0. " << endl;
        cout << "Enter the number of electors in this district: ";
        cin >> numOfElectors;
    }
    cout << "Divided District? (" << DIVIDEDDISTRICT << " for yes. " << DISTRICT << " for no) : ";
    cin >> district_type;
    while (district_type < DISTRICT || district_type > DIVIDEDDISTRICT) {
        cout << "Divided District? (" << DIVIDEDDISTRICT << " for yes. " << DISTRICT << " for no) : ";
        cin >> district_type;
    }

    elc.country.pushDistrict(name, numOfElectors, district_type);
    cout << "District added." << endl;
    pressChar();
}
void printStatus(Election &elc) {
    cout << "Date: " << elc.getDay() << "/" << elc.getMonth() << "/" << elc.getYear() << endl;
    cout << "Country: " << elc.country.getName() << " | number of citizens: " << elc.country.getNumOfCitizens() << " | number of districts: " << elc.country.getNumOfDistricts();
    cout << "| number of parties: " << elc.country.getNumOfParties() << "| Total number of electors: " << elc.country.getNumOfTotalElectors() << endl;
}
void insertParty(Election &elc) {
    string name;
    int id;
    cout << "Enter Party name: ";
    cin.ignore(1, '\n'); //ignores one '\n'
    getline(cin, name);
    cout << "Enter prime id: ";
    cin >> id;
    try {
        elc.country.pushParty(name, id);
    }
    catch (exception &ex) {
        cout << "ERROR. " << ex.what() << endl;
        pressChar();
        return;
    }
    cout << "Party added." << endl;
    pressChar();
}
void insertCitizen(Election &elc) {
    string name;
    string id;
    int district_id, year;
    if (elc.country.getNumOfDistricts() == 0) {
        cout << "Please enter a District before and try again." << endl;
        pressChar();
        return;
    }
    cout << "Enter citizen name: ";
    cin.ignore(1, '\n'); //ignores one '\n'
    getline(cin, name);
    cout << "Enter citizen id: ";
    cin >> id;
    while (id.length() != 9) {
        cout << "Citizen id must be 9 digits." << endl;
        cout << "Enter citizen id: ";
        cin >> id;
    }
    cout << "Enter citizen year of birth: ";
    cin >> year;
    while (elc.getYear() - year < 18) {
        cout << "Citizen age must be at least 18." << endl;
        cout << "Enter citizen year of birth: ";
        cin >> year;
    }
    cout << "Enter citizen district id (0-" << elc.country.getNumOfDistricts() - 1 << "): ";
    cin >> district_id;
    while (district_id < 0 || district_id > elc.country.getNumOfDistricts() - 1) {
        cout << "Id is not in range." << endl;
        cout << "Enter citizen district id (0-" << elc.country.getNumOfDistricts() - 1 << "): ";
        cin >> district_id;
    }
    try {
        elc.country.pushCitizen(name, atoi(id.c_str()), year, district_id);
    }
    catch (exception &ex) {
        cout << "ERROR." << ex.what() << endl;
        pressChar();
        return;
    }
    cout << "Citizen added." << endl;
    pressChar();
}
void pressChar() {
    string tmp;
    cout << "Enter any char to continue..." << endl;
    cin >> tmp;
}
void insertElector(Election &elc) {
    if (elc.country.getNumOfParties() == 0) {
        cout << "Please enter a party before and try again." << endl;
        pressChar();
        return;
    }
    int id, district_id, party_id;
    cout << "Enter id of elector: ";
    cin >> id;
    cout << "Enter party id (0-" << elc.country.getNumOfParties() - 1 << ") :";
    cin >> party_id;
    while (party_id < 0 || party_id >= elc.country.getNumOfParties()) {
        cout << "Party id is not in range." << endl;
        cout << "Enter party id (0-" << elc.country.getNumOfParties() - 1 << ") :";
        cin >> party_id;
    }
    cout << "Enter district number (0-" << elc.country.getNumOfDistricts() - 1 << "): ";
    cin >> district_id;
    while (district_id < 0 || district_id >= elc.country.getNumOfDistricts()) {
        cout << "District number is not in range." << endl;
        cout << "Enter district id (0-" << elc.country.getNumOfParties() - 1 << ") :";
        cin >> district_id;
    }
    try {
        elc.country.addElector(id, party_id, district_id);
    }
    catch (exception &ex) {
        cout << "ERROR. " << ex.what() << endl;
        pressChar();
        return;
    }
    cout << "Elector added." << endl;
    pressChar();
}
void addVote(Election &elc) {
    int party_id, citizen_id;
    if (elc.country.getNumOfParties() == 0) {
        cout << "There are no parties please enter party first." << endl;
        pressChar();
        return;
    }
    cout << "Enter citizen id: ";
    cin >> citizen_id;
    cout << "Enter party id (0-" << elc.country.getNumOfParties() - 1 << ") : ";
    cin >> party_id;
    while (party_id < 0 || party_id > elc.country.getNumOfParties() - 1) {
        cout << "Party id is not in range." << endl;
        cout << "Enter party id (0-" << elc.country.getNumOfParties() - 1 << ") : ";
        cin >> party_id;
    }
    try {
        elc.country.addVote(citizen_id, party_id);
    }
    catch (exception &ex) {
        cout << "ERROR. " << ex.what() << endl;
        pressChar();
        return;
    }
    cout << "Citizen Voted!" << endl;
    pressChar();
}
void getDate(int &day, int &month, int &year) // return current date of the user computer
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
}
void printMenu() { // prints the Main Menu interface
    cout << "Main Menu: Choose number between " << Input::zero << "-" << Input::eleven << endl;
    cout << Input::one << ". Insert District" << endl;
    cout << Input::two << ". Insert Citizen" << endl;
    cout << Input::three << ". Insert Party" << endl;
    cout << Input::four << ". Insert elector as party Candidate" << endl;
    cout << Input::five << ". Print all districts" << endl;
    cout << Input::six << ". Print all citizens" << endl;
    cout << Input::seven << ". Print all parties" << endl;
    cout << Input::eight << ". VOTE!" << endl;
    cout << Input::nine << ". Print current election status" << endl;
    cout << Input::ten << ". Save current election" << endl;
    cout << Input::eleven << ". Load election from file" << endl;
    cout << Input::zero << ". Exit program" << endl;
    cout << "Your input (" << Input::zero << "-" << Input::eleven << "): ";
}
void saveElection(Election &elc) {
    string fileName;
    cout << "Enter file name to save: " << endl;
    cin >> fileName;
    ofstream outfile(fileName.c_str(), ios::binary);
    if (!outfile) {
        cout << "ERROR: file not opened" << endl;
        pressChar();
        return;
    }
    try {
        elc.save(outfile);
    }
    catch (exception &ex) {
        outfile.close();
        cout << "ERROR." << ex.what() << endl;
        pressChar();
        return;
    }
    cout << "File saved successfully" << endl;
    pressChar();
    outfile.close();
}
void electionLoad(Election **election) {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    ifstream infile(fileName.c_str(), ios::binary);
    if (!infile) {
        cout << "ERROR: File did not open." << endl;
        exit(1);
    }
    try {
        *election = new Election(infile);
    }
    catch (exception &ex) {
        infile.close();
        cout << "ERROR. " << ex.what() << endl;
        exit(1);
    }
    infile.close();
}
void printSelectElectionMenu() {
    cout << Input::one << ". Start new election" << endl;
    cout << Input::two << ". Load election file" << endl;
    cout << Input::zero << ". Exit" << endl;
}
void printStartNewElectionMenu() {
    cout << Input::one << ". Regular Election" << endl;
    cout << Input::two << ". Simple Election" << endl;
}
Election *createElection() {
    Election *election = nullptr;
    int year, month, day;
    getDate(day, month, year);
    int input;

    printSelectElectionMenu();
    cin >> input;
    while ((input < Input::zero) || (input > Input::two)) {
        printSelectElectionMenu();
        cin >> input;
    }
    if (input == Input::zero) {
        cout << "Goodbye :)" << endl;
        exit(1);
    }

    if (input == Input::one)      // +Start new election+
    {
        election = startNewElection(year, month, day);
    }
    else if (input == Input::two) // +Load election file+
    {
        electionLoad(&election);
    }
    return election;
}
Election *startNewElection(int year, int month, int day) {
    string country_name;
    int electorsAmount;
    int input;
    printStartNewElectionMenu();
    cin >> input;
    while ((input < Input::one) || (input > Input::two)) {
        printStartNewElectionMenu();
        cin >> input;
    }
    cout << "Enter Country name: " << endl;
    cin >> country_name;
    if (input == Input::one) {      // Regular Election
        electorsAmount = 0;
    }
    else if (input == Input::two) { // Simple Election
        cout << "Enter the amount of electors: ";
        cin >> electorsAmount;
    }
    bool is_regularElection = (input == Input::one); // check if Regular Election

    Election *election;
    try {
        election = new Election(year, month, day, country_name, is_regularElection, electorsAmount);
    }
    catch (exception &) { // check if election creation had failed
        cout << "ERROR: Failed to create election, exiting program..." << endl;
        exit(1);
    }
    return election;
}

