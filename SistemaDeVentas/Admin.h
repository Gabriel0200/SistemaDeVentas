#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <string>
using namespace std;

class Admin {
private:
    unsigned int _id;
    string _fullName;
public:
    Admin() {}
    Admin(unsigned int _id, string _fullname) :_id(_id), _fullName(_fullName){}
    ~Admin() {}
    unsigned int getId() { return this->_id; }
    void setName(string fullName) { this->_fullName = fullName; }
    string getName() { return this->_fullName; }
    string toString() { return "Id: " + to_string(this->_id); }
};

#endif