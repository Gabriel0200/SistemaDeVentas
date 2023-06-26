#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <iostream>
#include <string>

class Supplier {
private:
    int _id;
    std::string _companyName;
    int _RUC;
    int _phoneNumber;
    std::string _email;

public:
    Supplier() {}

    Supplier(int id, std::string name, int phone, std::string email, int ruc)
        : _id(id), _companyName(name), _phoneNumber(phone), _email(email), _RUC(ruc) {}

    ~Supplier() {}

    int getId() const { return this->_id; }
    void setName(const std::string& fullName) { this->_companyName = fullName; }
    std::string getName() const { return this->_companyName; }
    void setPhoneNumber(int phoneNumber) { this->_phoneNumber = phoneNumber; }
    int getPhoneNumber() const { return this->_phoneNumber; }
    void setRuc(int ruc) { this->_RUC = ruc; }
    int getRuc() const { return this->_RUC; }

    friend std::ostream& operator<<(std::ostream& os, const Supplier& a) {
        os << a._id << "," << a._companyName << "," << a._phoneNumber << "," << a._email << "," << a._RUC;
        return os;
    }
};

#endif