#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <string>
using namespace std;
typedef unsigned int ui;

class Client {
private:
    ui _id;
    string _fullName;
    ui _phoneNumber;
    string _email;
    string _adress;
public:
    Client() {}
    Client(int id, string name, int phone, string email, string adress) :_id(id), _fullName(name), _phoneNumber(phone), _email(email), _adress(adress) {}
    ~Client() {}
    ui getId() { return this->_id; }
    void setName(string fullName) { this->_fullName = fullName; }
    string getName() { return this->_fullName; }
    void setPhoneNumber(ui phoneNumber) { this->_phoneNumber = phoneNumber; }
    ui getPhoneNumber() { return this->_phoneNumber; }
    void setAdress(string adress) { this->_adress = adress; }
    string getAdress() { return this->_adress; }
    string toString() { return "Id: " + to_string(this->_id) + " | Nombre Completo: " + this->_fullName + " | Celular: " + to_string(this->_phoneNumber) + " | Direccion: " + this->_adress + " | Correo: " + this->_email; }
};

#endif