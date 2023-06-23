#ifndef SUPPLIER_H
#define SUPPLIER_H
#include <iostream>
#include <string>
using namespace std;
typedef unsigned int ui;

class Supplier {
private:
    ui _id;
    string _companyName;
    ui _RUC;
    ui _phoneNumber;
    string _email;
public:
    Supplier() {}
    Supplier(int id, string name, int phone, string email, ui ruc) :_id(id), _companyName(name), _phoneNumber(phone), _email(email), _RUC(ruc) {}
    ~Supplier() {}
    ui getId() { return this->_id; }
    void setName(string fullName) { this->_companyName = fullName; }
    string getName() { return this->_companyName; }
    void setPhoneNumber(ui phoneNumber) { this->_phoneNumber = phoneNumber; }
    ui getPhoneNumber() { return this->_phoneNumber; }
    void setRuc(ui ruc) { this->_RUC = ruc; }
    ui getRuc() { return this->_RUC; }
    string toString() { return "Id: " + to_string(this->_id) + " | Nombre de la Compania: " + this->_companyName + " | Numero de contacto " + to_string(this->_phoneNumber) + " | Correo: " + this->_email + " | RUC: " + to_string(this->_RUC); }
};

#endif