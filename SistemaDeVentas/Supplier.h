#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <iostream>
#include <string>

class Supplier {
private:
    int _id, _phone, _ruc;
    std::string _cName, _email;

public:
    Supplier(int id = 0, std::string cName = "", int phone = 0, std::string email ="", int ruc = 0)
        :_id(id), _cName(cName), _phone(phone), _email(email), _ruc(ruc) {}

    int getRuc() {
        return this->_ruc;
    }

    std::string getName() {
        return this->_cName;
    }

    int getPhone() {
        return this->_phone;
    }

    int getId() {
        return this->_id;
    }
    std::string getEmail() {
        return this->_email;
    }
    friend std::ostream& operator<<(std::ostream& os, const Supplier& a) {
        os << a._id << "," << a._cName << ", " << a._phone << ", " << a._email << ", " << a._ruc;
        return os;
    }
};
#endif // Supplier_H