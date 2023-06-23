#ifndef DELIVERYDATABASE_H
#define DELIVERYDATABASE_H
#include <fstream>
#include <sstream>
#include "Delivery.h"
#include "BST.h"

class DeliveryDatabase {
	BinarySearchTree<Delivery>* tree;
public:
	DeliveryDatabase() {
		tree = new BinarySearchTree<Delivery>(
			[](Delivery d) -> void {
				std::cout << d << "\n";
			},
			[](Delivery a, Delivery b) -> bool {
				return a.getId() > b.getId();
			});		
	}
	~DeliveryDatabase(){}
	void load_data() {
		std::ifstream file("delivery_dataset.csv");
		if (!file.is_open()) {
			std::cout << "\nEl archivo delivery_dataset.csv no existe";
			return;
		}
		std::string line;
		while (getline(file, line)) {
			std::stringstream s(line);
			unsigned int id;
			std::string address, status;
			std::string aux;
			getline(s, aux, ',');
			id = stoi(aux);
			getline(s, aux, ',');
			address = aux;
			Delivery d = Delivery(id, address);
			this->tree->insert(d);
		}		
		file.close();
	}
	void display() {
		cout << "Deliveries del mes: " << "\n";
		this->tree->preOrder();
	}
	void showByStatus(int status) { //1 = En proceso, 2 = Entregado, 3 = Cancelado
		/*if (status == 1) {
			Delivery del = Delivery();
			del.setStatus("En proceso");
			auto comp = [](Delivery a, Delivery b)-> bool {
				return a < b;
			};
			auto equals = [](Delivery a, Delivery b)-> bool {
				return a.getStatus() == b.getStatus();
			};
			auto insert = [](Delivery a)->void {
				a.displayDeliveries();
			};
			this->tree->findByCriteria(del, equals, comp, insert);
		}*/		
		if (status == 1) {
			auto equals = [](Delivery a)-> bool {
				if (a.getStatus() == "En proceso") return true;
				return false;
			};		
			cout << "Se muestran todos los deliveries en proceso:" << "\n";
			for (unsigned int i = 0; i < this->tree->getNodes(equals).size(); ++i) {
				cout << this->tree->getNodes(equals)[i]->value << "\n";
			}		
		}	
		if (status == 2) {
			auto equals = [](Delivery a)-> bool {
				if (a.getStatus() == "Entregado") return true;
				return false;
			};
			cout << "Se muestran todos los deliveries entregados:" << "\n";
			for (unsigned int i = 0; i < this->tree->getNodes(equals).size(); ++i) {
				cout << this->tree->getNodes(equals)[i]->value << "\n";
			}
		}
		if (status == 3) {
			auto equals = [](Delivery a)-> bool {
				if (a.getStatus() == "Cancelado") return true;
				return false;
			};
			cout << "Se muestran todos los deliveries cancelados:" << "\n";
			for (unsigned int i = 0; i < this->tree->getNodes(equals).size(); ++i) {
				cout << this->tree->getNodes(equals)[i]->value << "\n";
			}
		}
	}
};

#endif
