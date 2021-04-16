

#include "CitizenList.h"
#include "LoaderHelper.h"

namespace elc {
    //constructor
    CitizenList::CitizenList() : votesCounter(0) {} //lst.size() initializes with '0' thanks to STL
    CitizenList::~CitizenList() {
        for (auto &i : lst) //delete all ListNodes
            delete i;
    }
    //constructor of ListNode:
    CitizenList::ListNode::ListNode(Citizen *ctzn) : citizen(ctzn) {}
    //setters
    void CitizenList::addVote() { // add vote to the party in this district
        votesCounter++;
    }
    void CitizenList::pushToList(Citizen *citizen)  //return false if citizen already in the list
    {
        if (citizen->isElector()) // if citizen already elector return false
            throw (runtime_error("Citizen already elector"));
        lst.push_back(new ListNode(citizen));
        citizen->setElector();
    }
    //prints
    bool CitizenList::printList(int n, std::ostream &os) const { //prints the first 'n' cells in the list --- (also compatible with different ostreams)
        if (n == -1) // we define that if (n == -1) we print all list. --- note that n = -1 is the default value
        {
            for (auto &p : lst) {
                os << *(p->citizen);
            }
            return true;
        }
        else // print until n or until the end
        {
            if (n > this->getListSize())
                return false;

            int i = 0;
            for (auto iter_i = lst.begin(); i < n; i++, iter_i++) {  //run for all the first 'n' elements
                os << *((*iter_i)->citizen);  //print citizen
            }
        }
        return true;
    }
    std::ostream &operator<<(std::ostream &os, CitizenList const &citlst) {
        citlst.printList(-1, os);
        return os;
    }
    //File functions
    void CitizenList::save(ostream &out) const {
        out.write(reinterpret_cast<const char *>(&votesCounter), sizeof(votesCounter));
        int listsize = this->getListSize();//write lst.size() :
        out.write(reinterpret_cast<const char *>(&listsize), sizeof(listsize));

        for (auto p: lst) {
            //for each citizen, We will remember to connect citizen_id in the CitizenList.load method --- by finding the correct pointer to this citizen thanks to the 'citizen_id' key
            int c_id = p->citizen->getId();/*!MUST BE THE LAST (OR THE FIRST) in the load, so we could read the 'citizen_id' in CitizenList.load!*/
            out.write(reinterpret_cast<const char *>(&c_id), sizeof(c_id));
        }
        if (!out.good())
            throw (runtime_error("CitizenList save failed."));
    }
    void CitizenList::load(istream &in) {
        //load local variables:
        in.read(reinterpret_cast<char *>(&votesCounter), sizeof(votesCounter));
        int listsize; // read lst.size(), and set it:
        in.read(reinterpret_cast<char *>(&listsize), sizeof(listsize));
        this->lst.resize(listsize);
        if (!in.good())
            throw (runtime_error("CitizenList load failed."));
        lst.clear();//resets the list
        //load 'lst':
        //convert citizen_id to pointer of citizen, and insert it as a ListNode to the list:
        int citizen_id;
        Citizen *citizen;
        for (int i = 0; i < listsize; i++) {//for each citizen needs to be inserted:
            in.read(reinterpret_cast<char *>(&citizen_id), sizeof(citizen_id));//read its ID
            if (!in.good())
                throw (runtime_error("CitizenList load failed."));
            //find the correct pointer to this citizen by its ID, and connect it to the list
            citizen = my_find<DynamicArray<elc::Citizen *> &, elc::Citizen *, int>(elc::LoaderHelper::getInstance()->getCitizens(), citizen_id);//return pointer to citizen if found. else return nullptr
            //create a dynamic ListNode for this citizen, and insert it as a ListNode in the CitizenList:
            lst.push_back(new ListNode(citizen));
        }
        if (!in.good())
            throw (runtime_error("CitizenList load failed."));
    }
}
