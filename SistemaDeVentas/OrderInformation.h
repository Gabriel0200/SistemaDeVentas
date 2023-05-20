#ifndef ORDERINFORMATION_H
#define ORDERINFORMATION_H

#include "CustomerDatabase.h"
#include "Client.h"
#include "ShoppingCart.h"
#include <functional>

typedef unsigned int ui;

class OrderInformation {
private:
    CustomerDatabase _clientlist;
    Client _client;
    float _price;
    string _name;
public:
    OrderInformation(DoublyLinkedList<Client> lista) {
        this->_clientlist.set_list(lista);
        this->_name = " ";
        this->_price = NULL;
    }
    void getOrder(string name, float price, ShoppingCart* shoppingCart) {
        setClientName(name);
        setPrice(price);
        auto search = [this](Client c)->bool {
            if (_name == c.getName()) {
                return true;
            }
            else return false;
        };
        if (this->_clientlist.get_list().search_by_value(search)) {
            this->_client = _clientlist.get_list().return_by_value(search);
            std::cout << "Datos del cliente: " << std::endl;
            std::cout << this->_client.toString() << std::endl;
            std::cout << "Productos Comprados por " + this->_client.getName() << std::endl;
            shoppingCart->showShoppingCart();
            std::cout << "EL precio Total por la compra es de: $" << this->_price << std::endl;
        }
    }
    void setClientName(string name) { this->_name = name; }
    void setPrice(float price) { this->_price = price; }
};
#endif