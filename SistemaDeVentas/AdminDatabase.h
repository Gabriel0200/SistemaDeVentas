#ifndef ADMINDATABASE_H
#define ADMINDATABASE_H
#include <fstream>
#include <sstream>
#include <iostream>
#include "Admin.h"
#include "BST.h"

class AdminDatabase {
	BinarySearchTree<Admin>* _adminTree;

public:
	AdminDatabase() {
		_adminTree = new BinarySearchTree<Admin>(
			[](Admin a) -> void {
				std::cout << a.toString() << "\n";
			},
			[](Admin a, Admin b) -> bool {
				return a.getId() > b.getId();
			});
	}
	~AdminDatabase() {}

	void load_data() {
		std::ifstream file("adminDataset.csv");
		if (!file.is_open()) {
			std::cout << "\nEl archivo adminDataset.csv no existe";
			return;
		}
		std::string line, name, aux;
		unsigned int id;
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			getline(ss, aux, ',');
			id = stoi(aux);
			getline(ss, aux, ',');
			name = aux;
			_adminTree->insert(Admin(id, name));
		}
		file.close();
	}
	/*BinarySearchTree<Admin>* get_tree() {
		return _adminTree;
	}*/
	bool verifyAdmin(unsigned int adminLoginID) {
		auto equals = [adminLoginID](Admin a)-> bool {
			if (a.getId() == adminLoginID) return true;
			return false;
		};
		if (this->_adminTree->find(equals) == true) return true;
	}
};
#endif