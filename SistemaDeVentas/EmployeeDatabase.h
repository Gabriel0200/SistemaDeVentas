#ifndef EMPLOYEEDATABASE_H
#define EMPLOYEEDATABASE_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Employee.h"
#include "AVL.h" 

using namespace std;

class EmployeeDatabase {
	AVLTree<Employee>* _EmployeeAVLSalary;
	AVLTree<Employee>* _EmployeeAVLName;
	Employee _employed;
public:
	EmployeeDatabase() {
		_EmployeeAVLSalary = new AVLTree<Employee>(
			[](Employee a) -> void {
				cout << a << endl;
			},
			[](Employee a, Employee b) -> bool {
				return a.getSalary() >= b.getSalary();
			});
		_EmployeeAVLName = new AVLTree<Employee>(
			[](Employee a) -> void {
				cout << a << endl;
			},
			[](Employee a, Employee b) -> bool {
				return a.getFullName() > b.getFullName();
			});
		_employed = Employee();
	}
	~EmployeeDatabase() {}

	void load_data() {
		ifstream file("EmployedDataset.csv");
		if (!file.is_open()) {
			cout << "\nEl archivo EmployedDataset.csv no existe";
			return;
		}
		string line;
		while (getline(file, line)) {
			string fullName, aux;
			int code, age;
			float salary;
			stringstream ss(line);
			getline(ss, aux, ',');
			try {
				code = stoi(aux);
			}
			catch (const std::invalid_argument& e) {
				cout << "Error al convertir el código a int: " << e.what() << endl;
				continue;
			}
			getline(ss, aux, ',');
			fullName = aux;
			getline(ss, aux, ',');
			try {
				age = stoi(aux);
			}
			catch (const std::invalid_argument& e) {
				cout << "Error al convertir la edad a int: " << e.what() << endl;
				continue;
			}
			getline(ss, aux, ',');
			try {
				salary = stof(aux);
			}
			catch (const std::invalid_argument& e) {
				cout << "Error al convertir el salario a float: " << e.what() << endl;
				continue;
			}
			Employee a(code, fullName, age, salary);
			_EmployeeAVLSalary->insert(a);
			_EmployeeAVLName->insert(a);
		}
		file.close();
	}

	void display() {
		cout << "Empleados en el sistema: " << endl;
		this->_EmployeeAVLSalary->preOrder();
	}

	void inOrderSalary() {
		cout << "Empleados en el sistema en orden por de Salarios: " << endl;
		this->_EmployeeAVLSalary->inOrder();
	}
	void inOrderName() {
		cout << "Empleados en el sistema en orden por Nombre: " << endl;
		this->_EmployeeAVLName->inOrder();
	}

	void findEmployed(int employedCode) {
		string employedName = "";
		auto equals = [employedCode, &employedName](Employee a) -> bool {
			if (a.getCode() == employedCode) {
				employedName = a.getFullName();
				return true;
			}
			return false;
		};
		if (this->_EmployeeAVLSalary->find(equals) == true) {
			cout << "Codigo " << employedCode << " - Nombre: "<< employedName << " encontrado" << endl;
			cout << this->_EmployeeAVLSalary->getNode(equals) << endl;
		}
		else cout << "Codigo " << employedCode << " - Nombre " << employedName << " no encontrado" << endl;
	}
	void isPerfectAVL() {
		if (this->_EmployeeAVLSalary->isPerfect() == true) cout << "El arbol es perfecto" << endl;
		else cout << "El arbol no es perfecto" << endl;
	}
	string getEmployedName() {
		return _employed.getFullName();
	}
};

#endif // EMPLOYEEDATABASE_H