#ifndef LOGIN_H
#define LOGIN_H
//#include <iostream>
#include "DoublyLinkedList.h"
#include "CustomerDatabase.h"
#include "Client.h"

class Login {
private:
    CustomerDatabase _clientList;
    Client _client;
    string _nameLogin;
public:
    Login(DoublyLinkedList<Client> lista, string nameLogin) {
        this->_clientList.set_list(lista);
        this->_nameLogin = nameLogin;
    };
    ~Login() {};
    bool verify() {
        auto search = [this](Client c)->bool {
            if (_nameLogin == c.getName()) {
                return true;
            }
            return false;
        };
        if (this->_clientList.get_list().search_by_value(search)) {
            return true;
        }
        return false;
    };
    void setUser(string nameLogin) { this->_nameLogin = nameLogin; }
    string getNameLogin() {
        return this->_nameLogin;
    }
    Client getUser() { return this->_client; };
};
#endif