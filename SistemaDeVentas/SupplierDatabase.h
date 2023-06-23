#ifndef SUPPLIERDATABASE_H
#define SUPPLIERDATABASE_H
#include <fstream>
#include <sstream>
#include <iostream>
#include "Supplier.h"
#include "DoublyLinkedList.h"
//#include <string>

class SupplierDatabase {
	DoublyLinkedList<Supplier> supplier_l;

public:
	SupplierDatabase() {}
	~SupplierDatabase() {}

	void load_data() {
		std::ifstream file("Supplier_BD.txt");
		std::string supplier, tmp, cname, email;
		ui id, phone, ruc;
		while (std::getline(file, supplier)) {
			std::stringstream ss(supplier);
			getline(ss, tmp, ',');
			id = stoi(tmp);
			getline(ss, tmp, ',');
			cname = tmp;
			getline(ss, tmp, ',');
			phone = stoi(tmp);
			getline(ss, tmp, ',');
			email = tmp;
			getline(ss, tmp);
			ruc = stoi(tmp);
			supplier_l.pushBack(Supplier(id, cname, phone, email, ruc));
		}
		file.close();
	}
	DoublyLinkedList<Supplier> get_list() {
		return supplier_l;
	}
	void set_list(DoublyLinkedList<Supplier> list) {
		supplier_l = list;
	}
};
#endif