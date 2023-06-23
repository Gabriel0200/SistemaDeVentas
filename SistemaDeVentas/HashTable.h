#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <functional>
#include <string>

template<class T>
class HashTable {
private:
	class Element {
	public:
		std::string key;
		T value;
	};
	Element** _hashTable;
	size_t _size;
	size_t _capacity;
private:
	int _hashFunction(std::string key) {
		int res = 0;
		for (unsigned int i = 0; i < key.length(); ++i)
			res += std::pow(static_cast<int>(key[i]), i + 1);
		return res % _capacity;
	}
	int _cuadraticProbing(int colisionIndex) {
		int jump = 1;
		int newIndex = colisionIndex;
		while (_hashTable[newIndex] != nullptr) {
			newIndex = colisionIndex;
			newIndex += pow(jump, 2);
			if (newIndex >= _capacity) newIndex %= _capacity;
			++jump;
		}
		return newIndex;
	}
	int _cuadraticProbingForReturnValues(int index, std::string key) {
		int jump = 1;
		int newIndex = index;
		while (_hashTable[newIndex]->key != key) {
			newIndex = index;
			newIndex += pow(jump, 2);
			if (newIndex >= _capacity) newIndex %= _capacity;
			++jump;
		}
		return newIndex;
	}
public:
	HashTable(size_t capacity) : _capacity(capacity) {
		_size = 0;
		_hashTable = new Element * [capacity];
		for (int i = 0; i < capacity; ++i) _hashTable[i] = nullptr;
	}
	void insert(std::string key, T value) {
		if (_size == _capacity) throw "Hash table is full";
		int index = _hashFunction(key);
		if (this->_hashTable[index] != nullptr) // Si es que esta posicion esta ocupada
			index = _cuadraticProbing(index);
		this->_hashTable[index] = new Element{ key, value };
		++_size;
	}
	T& operator[](std::string key) {
		int index = _hashFunction(key);
		if (this->_hashTable[index] != nullptr) // Si es que esta posicion esta ocupada
			index = _cuadraticProbing(index);
		this->_hashTable[index] = new Element{ key, T() };
		return this->_hashTable[index]->value;
	}
	T getCopy(std::string key) {
		int index = _hashFunction(key);
		return this->_hashTable[_cuadraticProbingForReturnValues(index, key)]->value;
	}
	void display(void (*show)(T)) {
		for (unsigned int i = 0; i < _capacity; ++i) {
			std::cout << "\nPos: " << i << ": ";
			if (_hashTable[i] == nullptr) {
				std::cout << "nullptr";
				continue;
			}
			show(_hashTable[i]->value);
		}
	}
	void erase(std::string key) {
		int index = _hashFunction(key);
		if (this->_size == 0) throw "HashTable is empty";

		while (this->_hashTable[index] != nullptr) {
			if (this->_hashTable[index]->key == key) {
				delete this->_hashTable[index];
				this->_hashTable[index] = nullptr;
				--_size;
			}
			++index;
		}
	}
	std::string* getKeys() {
		std::string* keys = new std::string[_size];
		int keysIndex = 0;
		for (int i = 0; i < _capacity; ++i) {
			if (_hashTable[i] != nullptr) {
				keys[keysIndex++] = _hashTable[i]->key;
			}
		}
		return keys;
	}
	void clear() {
		if (this->_size == 0) throw "Cannot clear an empty HashTable";
		for (int i = 0; i < _size; ++i) {
			this->_hashTable[i] = nullptr;
			delete this->_hashTable[i];
		}
		this->_size = 0;
		this->_capacity = 0;
	}
	size_t size() {
		return this->_size;
	}
	T* getValues() {
		T* values = new T[_size];
		int valueIndex = 0;
		for (int i = 0; i < _capacity; ++i) {
			if (_hashTable[i] != nullptr) {
				values[valueIndex++] = _hashTable[i]->value;
			}
		}
		return values;
	}
};
#endif