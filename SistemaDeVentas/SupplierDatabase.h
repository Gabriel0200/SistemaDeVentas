#ifndef SUPPLIERDATABASE_H
#define SUPPLIERDATABASE_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Supplier.h"
#include "AVL.h" 

class SupplierDatabase {
	AVLTree<Supplier>* _SupplierAVLRuc;
	AVLTree<Supplier>* _SupplierAVLName;
	Supplier _suppliers;
public:
	SupplierDatabase() {
		_SupplierAVLRuc = new AVLTree<Supplier>(
			[](Supplier a) -> void {
				cout << a << endl;
			},
			[](Supplier a, Supplier b) -> bool {
				return a.getRuc() >= b.getRuc();
			});
		_SupplierAVLName = new AVLTree<Supplier>(
			[](Supplier a) -> void {
				cout << a << endl;
			},
			[](Supplier a, Supplier b) -> bool {
				return a.getName() > b.getName();
			});
		_suppliers = Supplier();
	}
	~SupplierDatabase() {}

	void load_data() {
		ifstream file("SupplierDataset.csv");
		if (!file.is_open()) {
			cout << "\nEl archivo SupplierDataset.csv no existe";
			return;
		}
		string line;
		while (getline(file, line)) {
			string cName, aux, email; 
			int id, phone, ruc;
			stringstream ss(line);
			getline(ss, aux, ',');
			try {
				id = stoi(aux); 
			}
			catch (const std::invalid_argument& e) {
				cout << "Error al convertir el código a int: " << e.what() << endl;
				continue;
			}
			getline(ss, aux, ',');
			cName = aux; 
			getline(ss, aux, ',');
			try {
				phone = stoi(aux); 
			}
			catch (const std::invalid_argument& e) {
				cout << "Error al convertir la edad a int: " << e.what() << endl;
				continue;
			}
			getline(ss, aux, ',');
			email = aux;
			getline(ss, aux, ','); 
			try {
				ruc = stof(aux);
			}
			catch (const std::invalid_argument& e) {
				cout << "Error al convertir el salario a float: " << e.what() << endl;
				continue;
			}
			Supplier a(id, cName, phone, email, ruc);
			_SupplierAVLRuc->insert(a);
			_SupplierAVLName->insert(a);
		}
		file.close();
	}

	void display() {
		cout << "Provedores en el sistema: " << endl;
		this->_SupplierAVLRuc->preOrder();
	}

	void inOrderRuc() {
		cout << "Provedores en el sistema en orden por de Salarios: " << endl;
		this->_SupplierAVLRuc->inOrder();
	}
	void inOrderName() {
		cout << "Provedores en el sistema en orden por Nombre: " << endl;
		this->_SupplierAVLName->inOrder();
	}

	void findSuppliers(int suppliersCode) {
		string suppliersName = "";
		auto equals = [suppliersCode, &suppliersName](Supplier a) -> bool {
			if (a.getRuc() == suppliersCode) {
				suppliersName = a.getName();
				return true;
			}
			return false;
		};
		if (this->_SupplierAVLRuc->find(equals) == true) {
			cout << "Codigo " << suppliersCode << " - Nombre: " << suppliersName << " encontrado" << endl;
			cout << this->_SupplierAVLRuc->getNode(equals) << endl;
		}
		else cout << "Codigo " << suppliersCode << " - Nombre " << suppliersName << " no encontrado" << endl;
	}
	void isPerfectAVL() {
		if (this->_SupplierAVLRuc->isPerfect() == true) cout << "El arbol es perfecto" << endl;
		else cout << "El arbol no es perfecto" << endl;
	}
	string getSuppliersName() {
		return _suppliers.getName();
	}
};

#endif // SupplierDATABASE_H