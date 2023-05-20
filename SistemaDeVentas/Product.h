#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
//#include <string>
#include <fstream>
#include <sstream>
//using namespace std;
typedef unsigned int ui;

class Product {
	std::string id;
	std::string name;
	std::string code;
	std::string category;
	std::string price;

public:
	Product(std::string id, std::string code, std::string name, std::string price) : id(id), code(code), name(name), price(price) {
		this->category = "Electrodomestico";
	}
	Product() {}
	~Product() {}
	std::string toString() {
		return id + "," + code + ", " + category + "," + name + ", " + price;
	}
	std::string getName() { return this->name; }
	std::string getCode() { return this->code; }
	std::string getID() { return id; }
	std::string getPrice() {
		return price;
	}
};

#endif