#ifndef STACK_H
#define STACK_H

template <class T>
class Stack { // guardar el carrito de productos en la pila, si el cliente desea seguir comprando se guarda el stack y se procede con la orden de compra
	// si desea agregar más productos devuelve la pila
private:
	template <class t>
	class Node {
	private:
		t element;
		Node* next;
		Node* prev;
	public:
		Node(T c) {
			element = c;
			next = nullptr;
			prev = nullptr;
		}
		friend class Stack;
	};
	Node* start;
	size_t size;

public:
	Stack() {
		start = nullptr;
		size = 0;
	}
	void push(T e) {
		Node* _new = new Node<T>(e);
		if (start == nullptr) {
			start = _new;
			_new->next = start;
			_new->prev = start;
		}
		else {
			_new->next = start;
			_new->prev = start->prev;
			_new->next->prev = _new;
			_new->prev->next = _new;
			start = _new;
		}
		size++;
	}
	void pop() {
		if (size == 0)return;
		if (size == 1) {
			delete start;
		}
		else {
			start->next->prev = start->prev;
			start = start->next;
			delete start->prev->next;
			start->prev->next = start;
		}
		size--;
	}
	T peek() { //returns top element of the stack
		return start->element;
	}
	int capacity() {
		return size;
	}
	bool isEmpty() {
		return size == 0;
	}
};

#endif 