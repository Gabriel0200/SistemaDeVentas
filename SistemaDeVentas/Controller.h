#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Client.h"
#include "Admin.h"
#include "BST.h"
#include "AVL.h"
#include "AdminDatabase.h"
#include "DeliveryDatabase.h"
#include "BranchDatabase.h"
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
	DeliveryDatabase delivery_db;
	BranchDatabase branch_db;
	AdminDatabase admin_db; //inicializando adminDatabase
	ShoppingCart* shoppingCart_v;
	string currentAdmin;
	bool loginAdminVerify;
	bool loginVerify;
	bool productAdded;
	bool shoppingCartEmpty;
	float shoppingCartTotalPrice;
public:
	Controller() {
		this->client_l.set_list(listOfClients);
		this->product_l.set_list(listOfProducts);
		this->admin_db.load_data(); //leyendo de admindataset
		this->delivery_db.load_data(); //leyendo de deliverydataset
		this->branch_db.load_data(); //leyendo de branchdataset
		this->client_l.load_data();
		this->product_l.load_data();
		this->listOfClients = client_l.get_list();
		this->listOfProducts = product_l.get_list();
		this->loginAdminVerify = false;
		this->loginVerify = false;
		this->productAdded = false;
		this->shoppingCartEmpty = false;
		this->shoppingCart_v = new ShoppingCart(listOfProducts);
		this->shoppingCartTotalPrice = 0;
		this->orderInformation = new OrderInformation(listOfClients);
		this->currentAdmin = "";
	}
	//MÉTODOS PARA ADMIN
	void displayBranches() {
		this->branch_db.displayHashTable();
	}
	void searchHT(string location) {
		this->branch_db.searchByLocation(location);
	}
	void locationsReport() {
		this->branch_db.numOfBranchesByRegion();
	}
	void displayAdmins() {
		this->admin_db.display();
	}
	void displayDeliveries() {
		this->delivery_db.display();
	}
	void showByStatus(int status) {
		this->delivery_db.showByStatus(status);
	}
	void searchSibling(int id) {
		this->delivery_db.searchSibling(id);
	}
	void enterAdminId(unsigned int id) { //verifica si el ID de admin ingresado se encuentra en el dataset
		if (admin_db.verifyAdmin(id) == true) {
			loginAdminVerify = true;
			currentAdmin = admin_db.getAdminName();
		}
		else loginAdminVerify = false;
	}
	void findAdminByName(string name) {
		admin_db.findAdmin(name);
	}
	void inOrderAdminID() { //muestra el AVL de admins en orden por ID
		this->admin_db.inOrderID();
	}
	void inOrderAdminName() { //muestra el AVL de admins en orden por nombre
		this->admin_db.inOrderName();
	}
	void isAdminAVLPerfect() {
		this->admin_db.isPerfectAVL();
	}
	/////////////////////////////////////////////////
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
	bool get_loginAdminVerify() {
		return loginAdminVerify;
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
	string get_currentAdmin() {
		return currentAdmin;
	}
	void orderMerge() {
		shoppingCart_v->sortList();
		shoppingCart_v->showShoppingCart();
	}
};
#endif