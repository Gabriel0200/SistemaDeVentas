#ifndef BRANCHDATABASE_H
#define BRANCHDATABASE_H
#include <fstream>
#include <sstream>
#include "Branch.h"
#include "HashTable.h"

class BranchDatabase {
	HashTable<Branch>* htable;
public:
	BranchDatabase() {
		htable = new HashTable<Branch>(1000);
	}
	void load_data() {
		std::ifstream file("branch_dataset.csv");
		if (!file.is_open()) {
			std::cout << "\nEl archivo branch_dataset.csv no existe";
			return;
		}
		std::string line;
		while (getline(file, line)) {
			std::stringstream s(line);
			unsigned int id;
			std::string location;
			std::string aux;
			getline(s, aux, ',');
			id = stoi(aux);
			getline(s, aux, ',');
			location = aux;
			Branch b = Branch(id, location);
			htable->insert(std::to_string(id), b);
		}
		file.close();
	}
	void displayHashTable() {
		if (this->htable->size() > 0) {
			std::cout << "Se muestran las sucursales en un HashTable: ";
			this->htable->display([](Branch b) -> void { std::cout << b; });
			std::cout << "\n";
		}
		else {
			std::cout << "El HashTable se encuentra vacio" << "\n";
		}
	}
	void searchByLocation(string location) {
		auto equals = [location](Branch a)-> bool {
			if (a.getBranchLocation() == location) return true;
			return false;
		};
		cout << "Se muestran todas las sucursales en " << location << ":" << "\n";
		for (unsigned int i = 0; i < this->htable->getElements(equals).size(); ++i) {
			cout << this->htable->getElements(equals)[i]->value << "\n";
		}
	}
};

#endif