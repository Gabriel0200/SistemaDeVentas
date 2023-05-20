#ifndef CONTROLLER_H
#define CONTROLLER_H
#pragma once
#include "Client.h"
#include "DoublyLinkedList.h"
#include "OrderInformation.h"
#include "Product.h"
#include "CustomerDatabase.h"
#include "ProductDatabase.h"
#include "ShoppingCart.h"
#include "MyVector.h"
#include "Login.h"
#include <string>

class Controller {
	Login* login;
	OrderInformation* orderInformation;
	DoublyLinkedList<Client> listOfClients;
	DoublyLinkedList<Product> listOfProducts;
	CustomerDatabase client_l;
	ProductDatabase product_l;
	ShoppingCart* shoppingCart_v;
	bool loginVerify;
	bool productAdded;
	bool shoppingCartEmpty;
	float shoppingCartTotalPrice;
public:
	Controller() {
		this->client_l.set_list(listOfClients);
		this->product_l.set_list(listOfProducts);
		this->client_l.load_data();
		this->product_l.load_data();
		this->listOfClients = client_l.get_list();
		this->listOfProducts = product_l.get_list();
		this->loginVerify = false;
		this->productAdded = false;
		this->shoppingCartEmpty = false;
		this->shoppingCart_v = new ShoppingCart(listOfProducts);
		this->shoppingCartTotalPrice = 0;
		this->orderInformation = new OrderInformation(listOfClients);
	}
	void enterClientName(string fullName) {
		this->login = new Login(listOfClients, fullName);
		if (login->verify() == true) {
			loginVerify = true;
		}
		else loginVerify = false;
	}
	void seeProductList() {
		listOfProducts.display();
	}
	void chooseProducts(string codProd) {
		if (shoppingCart_v->addProduct(codProd) == true) {
			productAdded = true;
		}
		else productAdded = false;
	}
	void deleteShoppingCartProduct(string codeProduct) {
		shoppingCart_v->deleteByCode(codeProduct);
	}
	void clearShoppingCart() {
		if (shoppingCart_v->emptyShoppingCart() == true) {
			shoppingCartEmpty = true;
		}
		else shoppingCartEmpty = false;
	}
	void printShoppingCart() {
		shoppingCart_v->showShoppingCart();
	}
	void showPaidOrder() {
		int totalPrice = get_ShoppingCartTotalPrice();
		string userName = login->getNameLogin();
		orderInformation->getOrder(userName, totalPrice, shoppingCart_v);
	}
	float get_ShoppingCartTotalPrice() {
		shoppingCartTotalPrice = shoppingCart_v->getPrecioTotal();
		return shoppingCartTotalPrice;
	}
	bool get_loginVerify() {
		return loginVerify;
	}
	bool get_productAdded() {
		return productAdded;
	}
	bool get_shoppingCartEmpty() {
		return shoppingCartEmpty;
	}
};
#endif