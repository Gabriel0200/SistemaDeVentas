#ifndef SUPPLIERDATABASE_H
#define SUPPLIERDATABASE_H
#include <fstream>
#include <sstream>
#include <iostream>
#include "AVL.h"
#include "Supplier.h"
#include <string>

class SupplierDatabase {
	AVLTree<Supplier>* _SupplierAVLRuc;
	AVLTree<Supplier>* _SupplierAVLName;
	Supplier _Supplier;
public:
	SupplierDatabase() {
		_SupplierAVLRuc = new AVLTree<Supplier>(
			[](Supplier a) -> void {
				cout << a << endl;
			},
			[](Supplier a, Supplier b) -> bool {
				return a.getRuc() > b.getRuc();
			});
		_SupplierAVLName = new AVLTree<Supplier>(
			[](Supplier a) -> void {
				cout << a << endl;
			},
			[](Supplier a, Supplier b) -> bool {
				return a.getName() > b.getName();
			});
		_Supplier = Supplier();
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
			string tmp, cname, email;
			int id, phone, ruc; 
			stringstream ss(line);
			getline(ss, tmp, ',');
			try {
				id = stoi(tmp);
			}
			catch (const std::invalid_argument& e) {
				cout << "Error al convertir el id a int: " << e.what() << endl;
				continue;
			}
			getline(ss, tmp, ',');
			cname = tmp;
			getline(ss, tmp, ',');
			try {
				phone = stoi(tmp);
			}
			catch (const std::invalid_argument& e) {
				cout << "Error al convertir el phone a int: " << e.what() << endl;
				continue;
			}
			getline(ss, tmp, ',');
			email = tmp;
			getline(ss, tmp);
			try {
				ruc = stoi(tmp);
			}
			catch (const std::invalid_argument& e) {
				cout << "Error al convertir el ruc a int: " << e.what() << endl;
				continue;
			}
			Supplier a(id, cname, phone, email, ruc);
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
		cout << "Provedores en el sistema en orden por RUC: " << endl;
		this->_SupplierAVLRuc->inOrder();
	}
	void inOrderName() {
		cout << "Empleados en el sistema en orden por Nombre: " << endl;
		this->_SupplierAVLName->inOrder();
	}

	void findSupplier(int _supplierId) {
		string supplierName = "";
		auto equals = [_supplierId, &supplierName](Supplier a) -> bool {
			if (a.getId() == _supplierId) {
				supplierName = a.getName();
				return true;
			}
			return false;
		};
		if (this->_SupplierAVLRuc->find(equals) == true) {
			cout << "Codigo " << _supplierId << " - Nombre: " << supplierName << " encontrado" << endl;
			cout << this->_SupplierAVLRuc->getNode(equals) << endl;
		}
		else cout << "Codigo " << _supplierId << " - Nombre " << supplierName << " no encontrado" << endl;
	}
	void isPerfectAVL() {
		if (this->_SupplierAVLRuc->isPerfect() == true) cout << "El arbol es perfecto" << endl;
		else cout << "El arbol no es perfecto" << endl;
	}
	string getSupplierName() {
		return _Supplier.getName();
	}
};
#endif