#ifndef PRODUCTDATABASE_H
#define PRODUCTDATABASE_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Product.h"
#include "DoublyLinkedList.h"

class ProductDatabase {
	DoublyLinkedList<Product> product_l;
public:
	ProductDatabase() {}
	~ProductDatabase() {}

	void load_data() {
		std::ifstream file("product_dataset.csv");
		std::string idProduct, product, tmp, codeProduct, nameProduct, priceProduct;

		while (std::getline(file, product)) {
			std::stringstream ss(product);
			getline(ss, tmp, ',');
			idProduct = tmp;
			getline(ss, tmp, ',');
			codeProduct = tmp;
			getline(ss, tmp, ',');
			nameProduct = tmp;
			getline(ss, tmp);
			priceProduct = tmp;
			product_l.pushBack(Product(idProduct, codeProduct, nameProduct, priceProduct));
		}
		file.close();
	}
	DoublyLinkedList<Product> get_list() {
		return product_l;
	}
	void set_list(DoublyLinkedList<Product> list) {
		product_l = list;
	}
};
#endif