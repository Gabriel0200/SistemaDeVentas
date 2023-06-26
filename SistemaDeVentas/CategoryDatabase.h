#ifndef CATEGORYDATABASE_H
#define CATEGORYDATABASE_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Category.h"
#include "AVL.h" 

class CategoryDatabase {
	AVLTree<Category>* _CategoryAVLId;
	AVLTree<Category>* _CategoryAVLName;
	Category _Categories;
public:
	CategoryDatabase() {
		_CategoryAVLId = new AVLTree<Category>(
			[](Category a) -> void {
				std::cout << a << std::endl; 
			},
			[](Category a, Category b) -> bool {
				return a.getCode() >= b.getCode();
			});
		_CategoryAVLName = new AVLTree<Category>( 
			[](Category a) -> void {
				std::cout << a << std::endl;
			},
			[](Category a, Category b) -> bool {
				return a.getName() > b.getName();
			});
		_Categories = Category();
	}
	~CategoryDatabase() {} 

	void load_data() {
		std::ifstream file("CategoryDataset.csv");
		if (!file.is_open()) {
			std::cout << "\nEl archivo CategoryDataset.csv no existe";
			return;
		}
		std::string line;
		while (getline(file, line)) {
			std::string name, aux, description;  
			int code;
			std::stringstream ss(line); 
			getline(ss, aux, ','); 
			try {
				code = stoi(aux); 
			}
			catch (const std::invalid_argument& e) {
				std::cout << "Error al convertir el código a int: " << e.what() << std::endl;
				continue;
			}
			getline(ss, aux, ','); 
			name = aux; 
			getline(ss, aux, ',');
			description = aux;
			Category a(code, name, description); 
			_CategoryAVLId->insert(a); 
			_CategoryAVLName->insert(a); 
		}
		file.close();
	}

	void display() {
		std::cout << "Categoria en el sistema: " << std::endl; 
		this->_CategoryAVLId->preOrder();
	}

	void inOrderId() {
		std::cout << "Categoria en el sistema en orden por de id: " << std::endl; 
		this->_CategoryAVLId->inOrder(); 
	}
	void inOrderName() {
		std::cout << "Categoria en el sistema en orden por Nombre: " << std::endl;
		this->_CategoryAVLName->inOrder();
	}

	void findCategory(int categoryCode) {
		std::string categoryName = "";
		auto equals = [categoryCode, &categoryName](Category a) -> bool {
			if (a.getCode() == categoryCode) {
				categoryName = a.getName(); 
				return true;
			}
			return false;
		};
		if (this->_CategoryAVLId->find(equals) == true) {
			std::cout << "Codigo " << categoryCode << " - Nombre: " << categoryName << " encontrado" << std::endl;
			std::cout << this->_CategoryAVLId->getNode(equals) << std::endl;
		}
		else std::cout << "Codigo " << categoryCode << " - Nombre " << categoryName << " no encontrado" << std::endl;
	}
	void isPerfectAVL() {
		if (this->_CategoryAVLId->isPerfect() == true) std::cout << "El arbol es perfecto" << std::endl;
		else std::cout << "El arbol no es perfecto" << std::endl;
	}
	std::string getCategoryName() {
		return _Categories.getName(); 
	}
};
#endif