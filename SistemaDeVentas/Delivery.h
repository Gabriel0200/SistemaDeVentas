#ifndef DELIVERY_H
#define DELIVERY_H
#include <iostream>
#include "OrderInformation.h"
#include <string>
#include <vector>

std::string STATUS[] = {"Entregado", "En proceso", "Cancelado"};

class Delivery {
	unsigned int _clientId;
	std::string _clientAddress;
	std::string _status;	
	//std::vector<Delivery*>* deliveries;
public:
	Delivery(){}
	Delivery(unsigned int _clientId, std::string _clientAddress) : _clientId(_clientId), _clientAddress(_clientAddress) {
		this->_status = STATUS[rand() % 3];
		//this->deliveries = new vector<Delivery*>;
	}
	Delivery(std::string _status) : _status(_status){}
	/*Delivery(std::string _status) : _status(_status){
		this->deliveries = new vector<Delivery*>;
	
	}*/
	~Delivery(){}
	void setStatus(std::string status){
		this->_status = status;
	}
	unsigned int getId() {
		return this->_clientId;
	}
	std::string getStatus() {
		return this->_status;
	}
	std::string getAddress() {
		return this->_clientAddress;
	}
	friend ostream& operator<<(ostream& os, const Delivery& d) {
		os << d._clientId << ", " << d._clientAddress << ", " << d._status;
		return os;
	}
	bool operator<(const Delivery& d) { //<
		return (this->_status.compare(d._status));
	}
};

#endif
