#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H
#include <iostream>
#include "ProductDatabase.h"
#include "DoublyLinkedList.h"
#include "Client.h"
#include "MyVector.h"
typedef unsigned int ui;

class ShoppingCart {
    ProductDatabase _productList;
    ui quantity;
    float totalPrice;
    DoublyLinkedList<Product> cartList;
    MyVector<float>* vprecios;
    Product _product;
public:
    ShoppingCart(DoublyLinkedList<Product> lista) {
        this->quantity = 0;
        this->totalPrice = 0;
        this->cartList = DoublyLinkedList<Product>();
        this->_productList.set_list(lista);
        this->vprecios = new MyVector<float>();
    }
    ~ShoppingCart() {
        delete vprecios;
    }
    bool addProduct(string code) {
        auto search = [&](Product p)->bool {
            if (code == p.getCode()) {
                return true;
            }
            else return false;
        };
        if (this->_productList.get_list().search_by_value(search)) {
            this->_product = this->_productList.get_list().return_by_value(search);
            cartList.pushBack(_product);
            vprecios->push_back(stof(_product.getPrice()));
            return true;
        }
        else  return false;
    }
    void deleteByCode(string code) { //Los precios del vector no se borran todavía
        auto search = [&](Product p)->bool {
            if (code == p.getCode()) {
                vprecios->delete_by_price(stof(p.getPrice()));
                return true;
            }
            return false;
        };
        cartList.delete_by_value(search);
        //float price = stof(_product.getPrice());
    };
    bool emptyShoppingCart() {
        cartList.clear();
        totalPrice = 0;
        vprecios->clear();
        if (cartList.size() == 0) {
            return true;
        }
        return false;
    }
    void showShoppingCart() {
        if (cartList.size() == 0) {
            cout << "Su carrito se encuentra vacio" << endl;
        }
        else cartList.display();
    }
    ui getCartSize() {
        this->quantity = cartList.size();
        return quantity;
    }
    float getPrecioTotal() {
        this->totalPrice = 0;
        for (int i = 0; i < vprecios->size(); ++i) {
            totalPrice += vprecios->getVector(i);
        }
        return totalPrice;
    }
    void sortList() {
        this->cartList.mergeSort(this->cartList.getHead());
    }
};

#endif