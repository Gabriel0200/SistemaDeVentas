#ifndef __AVL_HPP__
#define __AVL_HPP__
#include <functional>

template<class T>
class AVLTree {
private:
    class Node {
    public:
        T value;
        Node* leftChild;
        Node* rightChild;
        int height;
    };
    Node* _root;
    size_t _size;
    std::function<void(T)> _show;
    std::function<bool(T, T)> _compare;
private:
    void _insert(Node*& n, T value) {
        if (n == nullptr) {
            n = new Node{ value, nullptr, nullptr, 0 };
            ++_size;
            return;
        }
        if (_compare(n->value, value)) _insert(n->leftChild, value);
        else _insert(n->rightChild, value);
        _setHeight(n);
        _balanceSubTree(n);
    }
    bool _isBalanced(Node* n) {
        int leftHeight, rightHeight;
        if (n == nullptr) return 1;

        leftHeight = _getHeight(n->leftChild);
        rightHeight = _getHeight(n->rightChild);

        if (abs(leftHeight - rightHeight) <= 1 && _isBalanced(n->leftChild) && _isBalanced(n->rightChild)) {
            return 1;
        }
        return 0;
    }
    void _preOrder(Node* n) {
        // if(n == nullptr) return;
        if (!n) return;
        _show(n->value); // 
        _preOrder(n->leftChild); // Izq
        _preOrder(n->rightChild); // Der
    }
    void _preOrderH(Node* n) {
        if (!n) return;
        _show(n->height); // 
        _preOrderH(n->leftChild); // Izq
        _preOrderH(n->rightChild); // Der
    }
    void _inOrder(Node* n) {
        // if(n == nullptr) return;
        if (!n) return;
        _inOrder(n->leftChild); // Izq
        _show(n->value); //       
        _inOrder(n->rightChild); // Der
    }
    void _inOrderH(Node* n) {
        // if(n == nullptr) return;
        if (!n) return;
        _inOrderH(n->leftChild); // Izq
        _show(n->height); //       
        _inOrderH(n->rightChild); // Der
    }
    void _leftRotation(Node*& n) {
        Node* rightChild = n->rightChild;
        // El hijo derecho del nodo apunta al hijo izquierdo del hijo derecho del nodo
        n->rightChild = rightChild->leftChild;
        rightChild->leftChild = n;
        _setHeight(n);
        _setHeight(rightChild);
        n = rightChild;
    }
    void _rightRotation(Node*& n) {
        Node* leftChild = n->leftChild;
        n->leftChild = leftChild->rightChild;
        leftChild->rightChild = n;
        _setHeight(n);
        _setHeight(leftChild);
        n = leftChild;
    }
    void _balanceSubTree(Node*& n) {
        int heightDifference = _getHeight(n->leftChild) - _getHeight(n->rightChild);
        if (heightDifference <= -2) {// Desbalanceado por la derecha
            if (n->rightChild->rightChild) {
                // Left rotation
                _leftRotation(n);
            }
            else {
                // Right-Left Rotation
                _rightRotation(n->rightChild);
                _leftRotation(n);
            }
        }
        else if (heightDifference >= 2) { // Desbalanceado por la izquierda
            if (n->leftChild->leftChild) {
                // RightRotation
                _rightRotation(n);
            }
            else {
                // Left-Right Rotation
                _leftRotation(n->leftChild);
                _rightRotation(n);
            }
        }
    }
    void _setHeight(Node* n) {
        n->height = std::max(_getHeight(n->leftChild), _getHeight(n->rightChild)) + 1;
    }
    int _getHeight(Node* n) {
        return (n) ? n->height : -1;
    }
    int _getDepth(Node* n) {
        int d = 0;
        while (n != nullptr) {
            ++d;
            n = n->leftChild;
        }
        return d;
    }
    bool _isPerfect(Node* n, int d, int level = 0) { //todos los nodos internos tienen dos hijos y todas las hojas están al mismo nivel
        if (n == nullptr) return true;
        if (n->leftChild == nullptr && n->rightChild == nullptr) return (d == level + 1);
        if (n->leftChild == nullptr || n->rightChild == nullptr) return false;
        return _isPerfect(n->leftChild, d, level + 1) && _isPerfect(n->rightChild, d, level + 1);
    }
    Node* _find(Node* n, std::function<bool(T)> equals) { //busqueda de un nodo segun criterio 
        if (n == nullptr) return nullptr;
        if (equals(n->value)) return n;

        Node* tmp = _find(n->leftChild, equals);
        if (tmp != nullptr) return tmp;

        tmp = _find(n->rightChild, equals);
        return tmp;
    }
public:
    AVLTree(std::function<void(T)> show, std::function<bool(T, T)> compare) : _show(show), _compare(compare) {
        _root = nullptr;
        _size = 0ll;
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
    void preOrderH() {
        _preOrderH(_root);
    }
    void inOrderH() {
        _inOrderH(_root);
    }
    bool isBalanced() {
        return _isBalanced(_root);
    }
    bool isPerfect() {
        int d = _getDepth(_root);
        return _isPerfect(_root, d);
    }
    bool find(std::function<bool(T)> equals) {
        if (_find(_root, equals) != nullptr) return true;
        return false;
    }
    T getNode(std::function<bool(T)> equals) {
        if (find(equals) == true) {
            return _find(_root, equals)->value;
        }
        else throw "Node not found";
    }
    // Rightmost element
    T max() {
        Node* aux = _root;
        while (aux->rightChild != nullptr) aux = aux->rightChild;
        return aux->value;
    }
    // Leftmost element
    T min() {
        Node* aux = _root;
        while (aux->leftChild != nullptr) aux = aux->leftChild;
        return aux->value;
    }
    //void IterativePreOrder() {
    //    std::stack<Node*> s;
    //    s.push(this->_root);
    //    while (s.empty() == false) {
    //        // Saco un nodo de la pila
    //        Node* n = s.top();
    //        s.pop();
    //        // Lo muestro en consola
    //        _show(n->value);
    //        // Inserto en la pila a sus hijos derecho e izquierdo,
    //        // en ese orden, en la pila (si es que no son nulos, claro)
    //        if (n->rightChild)
    //            s.push(n->rightChild);
    //        if (n->leftChild)
    //            s.push(n->leftChild);
    //    }
    //}
};
#endif