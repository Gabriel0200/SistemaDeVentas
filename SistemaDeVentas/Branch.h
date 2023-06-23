#ifndef BRANCH_H
#define BRANCH_H
#include <iostream>
#include <string>
using namespace std;

class Branch {
private:
    unsigned int _id;
    string _branchLocation;
public:
    Branch() {}
    Branch(unsigned int _id, string _branchLocation) :_id(_id), _branchLocation(_branchLocation) {}
    ~Branch() {}
    unsigned int getId() { return this->_id; }
    void setId(unsigned int id) { this->_id = id; }
    void setBranchLocation(string location) { this->_branchLocation = location; }
    string getBranchLocation() { return this->_branchLocation; }
    friend ostream& operator<<(ostream& os, const Branch& a) {
        os << a._id << ", " << a._branchLocation;
        return os;
    }
};

#endif