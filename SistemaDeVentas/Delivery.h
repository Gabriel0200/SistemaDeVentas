#ifndef DELIVERY_H
#define DELIVERY_H
#include <iostream>
#include "OrderInformation.h"
#include <string>

class Delivery {
	std::string _clientId;
	std::string _clientAddress;
	std::string _status;	
public:
	Delivery(){}
	Delivery(std::string _clientId, std::string _clientAddress, std::string _status)
		: _clientId(_clientId), _clientAddress(_clientAddress), _status(_status){
	}
	~Delivery(){}
	std::string getId() {
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
	bool operator<(const Delivery& d) {
		return (this->_status.compare(d._status));
	}
};

#endif
