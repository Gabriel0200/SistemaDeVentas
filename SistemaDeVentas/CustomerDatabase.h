#ifndef CUSTOMERDATABASE_H
#define CUSTOMERDATABASE_H
#include <fstream>
#include <sstream>
#include <iostream>
#include "Client.h"
#include "DoublyLinkedList.h"
//#include <string>

class CustomerDatabase {
	DoublyLinkedList<Client> client_l;

public:
	CustomerDatabase() {}
	~CustomerDatabase() {}

	void load_data() {
		std::ifstream file("Clientes_BD.txt");
		std::string client, tmp, name, adress, email;
		ui id, phone;
		while (std::getline(file, client)) {
			std::stringstream ss(client);
			getline(ss, tmp, ',');
			id = stoi(tmp);
			getline(ss, tmp, ',');
			name = tmp;
			getline(ss, tmp, ',');
			phone = stoi(tmp);
			getline(ss, tmp, ',');
			email = tmp;
			getline(ss, tmp);
			adress = tmp;
			client_l.pushBack(Client(id, name, phone, email, adress));
		}
		file.close();
	}
	DoublyLinkedList<Client> get_list() {
		return client_l;
	}
	void set_list(DoublyLinkedList<Client> list) {
		client_l = list;
	}
};
#endif