#ifndef BST_H
#define BST_H
#include <functional>

template<class T>
class BinarySearchTree {
private:
	using DisplayFunction = void (*)(T);
	using ComparisonCriteria = bool (*)(T, T);
	class Node {
	public:
		T value;
		Node* leftChild;
		Node* rightChild;
	};
	Node* _root;
	size_t _size;
	DisplayFunction _show;
	ComparisonCriteria _compare;
	void _insert(Node*& n, T value) {
		if (n == nullptr) {
			n = new Node{ value, nullptr, nullptr };
			return;
		}
		if (_compare(n->value, value)) _insert(n->leftChild, value);
		else _insert(n->rightChild, value);
	}
	Node* _remove(Node*& n, T value) {
		Node* temp = new Node;
		if (n == nullptr) return n;
		if (value < n->value) {
			n->leftChild = _remove(n->leftChild, value);
		}
		else if (value > n->value) {
			n->rightChild = _remove(n->rightChild, value);
		}
		else if (n->leftChild && n->rightChild) {
			temp = _minNode();
			n->value = temp->value;
			n->rightChild = _remove(n->rightChild, temp->value);
		}
		else {
			if (n->leftChild == nullptr) {
				temp = n->rightChild;
				free(n);
				return temp;
			}
			else if (n->rightChild == nullptr) {
				temp = n->leftChild;
				free(n);
				return temp;
			}
		}
		return n;
	}
	void _preOrder(Node* n) {
		if (!n) return;
		_show(n->value);
		_preOrder(n->leftChild);
		_preOrder(n->rightChild);
	}
	void _inOrder(Node* n) {
		if (!n) return;
		_inOrder(n->leftChild);
		_show(n->value);
		_inOrder(n->rightChild);
	}
	Node* _maxNode() {
		Node* aux = _root;
		while (aux->rightChild != nullptr) aux = aux->rightChild;
		return aux;
	}
	Node* _minNode() {
		Node* aux = _root;
		while (aux->leftChild != nullptr) aux = aux->leftChild;
		return aux;
	}
	Node* _find(Node* n, T value) { //busqueda de un nodo dado
		if (n == nullptr) return n;
		if (value < n->value) {
			return _find(n->leftChild, value);
		}
		else if (value > n->value) {
			return _find(n->rightChild, value);
		}
		else return n;
	}
	bool _isEmpty() {
		return _root == nullptr;
	}
	int _quantity(Node* n) { //cantidad de nodos en el BST
		if (n == nullptr) return 0;
		else {
			int lc, rc;
			lc = _quantity(n->leftChild);
			rc = _quantity(n->rightChild);
			return 1 + lc + rc;
		}
	}
	int _depth(Node* n, T value, std::function<bool(T, T)> equals) { //profundidad de un nodo dado
		if (n == nullptr) {
			return -1;
		}
		if (equals(n->value, value)) {
			return 0;
		}
		int leftDepth = _depth(n->leftChild, value, equals);
		int rightDepth = _depth(n->rightChild, value, equals);

		if (leftDepth != -1) {
			return leftDepth + 1;
		}
		else if (rightDepth != -1) {
			return rightDepth + 1;
		}
		else {
			return -1;
		}
	}
	int _leafs(Node* n) {
		if (n == nullptr) return 0;

		if (n->leftChild == nullptr && n->rightChild == nullptr) {
			return 1;
		}
		else {
			return _leafs(n->leftChild) + _leafs(n->rightChild);
		}
	}
	Node* _getSibling(Node* n, T value, std::function<bool(T, T)> equals) {
		if (n == nullptr || equals(n->value, value)) return nullptr;
		if (n->leftChild != nullptr && equals(n->leftChild->value, value)) {
			return n->rightChild;
		}
		if (n->rightChild != nullptr && equals(n->rightChild->value, value)) {
			return n->leftChild;
		}
		Node* tmp = _getSibling(n->leftChild, value, equals);
		if (tmp != nullptr) return tmp;
		tmp = _getSibling(n->rightChild, value, equals);
		return tmp;
	}
public:
	BinarySearchTree(DisplayFunction show, ComparisonCriteria compare) : _show(show), _compare(compare) {
		_root = nullptr;
		_size = 0ll;
	}
	T getSibling(T value, std::function<bool(T, T)> equals) {
		return _getSibling(_root, value, equals)->value;
	}
	int depth(T value, std::function<bool(T, T)> equals) {
		return _depth(_root, value, equals);
	}
	int quantity() {
		return _quantity(_root);
	}
	void insert(T value) {
		_insert(_root, value);
	}
	void preOrder() {
		_preOrder(_root);
	}
	void inOrder() {
		_inOrder(_root);
	}
	void remove(T value) {
		_remove(_root, value);
	}
	int leafs() {
		return _leafs(_root);
	}
	bool find(T value) {
		if (_find(_root, value)) {
			return true;
		}
		return false;
	}
	T max() {
		Node* aux = _root;
		while (aux->rightChild != nullptr) aux = aux->rightChild;
		return aux->value;
	}
	T min() {
		Node* aux = _root;
		while (aux->leftChild != nullptr) aux = aux->leftChild;
		return aux->value;
	}
};

#endif