#ifndef CONTROLLER_H
#define CONTROLLER_H
#pragma once
#include <string>
#include "Client.h"
#include "Admin.h"
#include "BST.h"
#include "AVL.h"
#include "AdminDatabase.h"
#include "DeliveryDatabase.h"
#include "DoublyLinkedList.h"
#include "OrderInformation.h"
#include "Product.h"
#include "Supplier.h"
#include "CustomerDatabase.h"
#include "SupplierDatabase.h"
#include "ProductDatabase.h"
#include "ShoppingCart.h"
#include "MyVector.h"
#include "Login.h"
#include "Report.h"
#include "CategoryDatabase.h"
#include <fstream>

class Controller {
	Login* login;
	OrderInformation* orderInformation;
	DoublyLinkedList<Client> listOfClients;
	DoublyLinkedList<Product> listOfProducts;
	CustomerDatabase client_l;
	ProductDatabase product_l;
	SupplierDatabase supplier_db;//inicializando SupplierDatabase
	DeliveryDatabase delivery_db;
	AdminDatabase admin_db; //inicializando adminDatabase
	CategoryDatabase category_db;
	ShoppingCart* shoppingCart_v;
	string currentAdmin;
	Report _report;
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
		this->client_l.load_data();
		this->product_l.load_data();
		this->supplier_db.load_data();//leyendo de supplierdataset
		this->category_db.load_data();
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
	void displayAdmins() {
		this->admin_db.display();
	}
	void displayDeliveries() {
		this->delivery_db.display();
	}
	void showByStatus(int status) {
		this->delivery_db.showByStatus(status);
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
				/// METODOS PROVEDOR ///
	void displaySupplier() {
		this->supplier_db.display();
	}
	void findSupplierByRuc(int code) {
		this->supplier_db.findSuppliers(code); //buscar empleado por Codigo
	}
	void inOrderASupplierRuc() { //muestra el AVL de admins en orden por el Salario
		this->supplier_db.inOrderRuc();
	}
	void inOrderSupplierName() { //muestra el AVL de admins en orden por el nombre
		this->supplier_db.inOrderName();
	}
	void isSupplierAVLPerfect() {
		this->supplier_db.isPerfectAVL();
	}
	////////////////////////////////////////////////
				/// Categoria ///
	void displayCategory() {
		this->category_db.display(); 
	}
	void findCategoryById(int code) {
		this->category_db.findCategory(code); //buscar empleado por Codigo
	}
	void inOrderACategoryId() { //muestra el AVL de admins en orden por el Salario
		this->category_db,inOrderACategoryId();
	}
	void inOrderCategoryName() { //muestra el AVL de admins en orden por el nombre
		this->category_db.inOrderName();
	}
	void isCategoryAVLPerfect() {
		this->category_db.isPerfectAVL();
	}
	////////////////////////////////////////////////
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
	void ventasRegistrada() {
		cout << "ventas realizadas:" << endl;
		cout << _report.getSuma() << endl; 
		int totalPrice = get_ShoppingCartTotalPrice();
		string userName = login->getNameLogin();
		orderInformation->getOrder(userName, totalPrice, shoppingCart_v);
	}
	void ventas() {
		_report.ventasSuma();
	}
};
#endif