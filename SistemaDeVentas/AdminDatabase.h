#ifndef ADMINDATABASE_H
#define ADMINDATABASE_H
#include <fstream>
#include <sstream>
#include <iostream>
#include "Admin.h"
#include "BST.h"
#include "AVL.h" 

class AdminDatabase {
	//BinarySearchTree<Admin>* _adminTree;
	AVLTree<Admin>* _adminAVLID;
	AVLTree<Admin>* _adminAVLName;
public:
	AdminDatabase() {
		/*_adminTree = new BinarySearchTree<Admin>(
			[](Admin a) -> void {
				std::cout << a << "\n";
			},
			[](Admin a, Admin b) -> bool {
				return a.getId() > b.getId();
			});*/
		_adminAVLID = new AVLTree<Admin>(
			[](Admin a) -> void {
				std::cout << a << "\n";
			},
			[](Admin a, Admin b) -> bool {
				return a.getId() > b.getId();
			});
		_adminAVLName = new AVLTree<Admin>(
			[](Admin a) -> void {
				std::cout << a << "\n";
			},
			[](Admin a, Admin b) -> bool {
				return a.getName() > b.getName();
			});
	}
	~AdminDatabase() {}

	void load_data() {
		std::ifstream file("adminDataset.csv");
		if (!file.is_open()) {
			std::cout << "\nEl archivo adminDataset.csv no existe";
			return;
		}
		string line;
		while (std::getline(file, line)) {
			std::string name, aux;
			unsigned int id;
			std::stringstream ss(line);
			getline(ss, aux, ',');
			id = stoi(aux);
			getline(ss, aux, ',');
			name = aux;
			Admin a = Admin(id, name);
			//_adminTree->insert(a);
			_adminAVLID->insert(a);
			_adminAVLName->insert(a);
		}
		file.close();
	}
	void display() {
		cout << "Administradores en el sistema: " << "\n";
		//this->_adminTree->preOrder();
		this->_adminAVLID->preOrder();
	}
	//Ordenamientos
	void inOrderID() {
		cout << "Administradores en el sistema en orden por ID: " << "\n";
		this->_adminAVLID->inOrder();
	}
	void inOrderName() {
		cout << "Administradores en el sistema en orden por Nombre: " << "\n";
		this->_adminAVLName->inOrder();
	}
	//Búsquedas
	bool verifyAdmin(unsigned int adminLoginID) {
		auto equals = [adminLoginID](Admin a)-> bool {
			if (a.getId() == adminLoginID) return true;
			return false;
		};
		if (this->_adminAVLID->find(equals) == true) return true;
		return false;
	}
	void findAdmin(string adminName) {
		auto equals = [adminName](Admin a)-> bool {
			if (a.getName() == adminName) return true;
			return false;
		};
		if (this->_adminAVLID->find(equals) == true) {
			cout << "Nombre " << adminName << " encontrado" << "\n";
		}else cout << "Nombre " << adminName << " no encontrado" << "\n";
	}
};
#endif