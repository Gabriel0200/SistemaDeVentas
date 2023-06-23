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
    Admin(unsigned int id, string fullName) :_id(id), _fullName(fullName){}
    ~Admin() {}
    unsigned int getId() { return this->_id; }
    void setId(unsigned int id) { this->_id = id; }
    void setName(string fullName) { this->_fullName = fullName; }
    string getName() { return this->_fullName; }
    friend ostream& operator<<(ostream& os, const Admin& a) {
        os << a._id << ", " << a._fullName;
        return os;
    }
};

#endif