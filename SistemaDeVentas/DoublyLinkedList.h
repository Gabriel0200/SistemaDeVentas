#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST
//#include <string>
#include <functional>

template <class T>
class DoublyLinkedList {
private:
    class Node {
        T value;
        Node* next;
        Node* back;
    public:
        Node(T value) : value(value), next(nullptr), back(nullptr) {}
        T getData() { return this->value; }
        Node* getNext() { return this->next; }
        Node* getBack() { return this->back; }
        friend class DoublyLinkedList;
    };
    Node* _start;
    Node* _end;
    size_t _size;
public:
    DoublyLinkedList() {
        this->_start = this->_end = nullptr;
        this->_size = 0;
    }
    void pushBack(T value) {
        Node* newNode = new Node(value);
        if (_size == 0) {
            this->_start = this->_end = newNode;
            _size = 1;
            return;
        }
        this->_end->next = newNode;
        newNode->back = this->_end;
        this->_end = this->_end->next;
        ++_size;
    }
    void pushFront(T value) {
        Node* newNode = new Node(value);
        if (_size == 0) {
            this->_start = this->_end = newNode;
            this->_size = 1;
            return;
        }
        newNode->next = this->_start;
        this->_start->back = newNode;
        this->_start = this->_start->back;
        ++_size;
    }
    void insertAt(T value, int pos) {
        if (pos < 0 || pos > _size) throw "Invalid position";
        if (pos == 0) { pushFront(value); return; }
        if (pos == _size) { pushBack(value); return; }
        Node* aux = this->_start;
        Node* newNode = new Node(value);
        for (unsigned int i = 0; i < pos - 1; ++i) aux = aux->next;
        newNode->next = aux->next;
        aux->next->back = newNode;
        aux->next = newNode;
        newNode->back = aux;
        ++_size;
    }
    void popBack() {
        if (this->_size == 0) throw "Cannot erase in empty list";
        if (this->_size == 1) {
            delete _start;
            this->_start = this->_end = nullptr;
            this->_size = 0;
            return;
        }
        this->_end = this->_end->back;
        this->_end->next->back = nullptr;
        delete this->_end->next;
        this->_end->next = nullptr;
        --_size;
    }
    void popFront() {
        if (this->_size == 0) throw "Cannot erase in empty list";
        if (this->_size == 1) {
            delete _start;
            this->_start = this->_end = nullptr;
            this->_size = 0;
            return;
        }
        this->_start = this->_start->next;
        this->_start->back->next = nullptr;
        delete this->_start->back;
        this->_start->back = nullptr;
        --_size;
    }
    void eraseAt(int pos) {
        if (pos < 0 || pos >= _size) throw "Cannot erase out of bounds";
        if (pos == 0) { popFront(); return; }
        if (pos == _size - 1) { popBack(); return; }
        Node* aux = this->_start;
        for (unsigned int i = 0; i < pos - 1; ++i) aux = aux->next;
        Node* toErase = aux->next;
        aux->next = aux->next->next;
        aux->next->back = aux->next->back->back;
        toErase->next = toErase->back = nullptr;
        delete toErase;
        --_size;
    }
    void swap(T& a, T& b) {
        T c = a;
        a = b;
        b = c;
    }
    void display() {
        Node* tmp = this->_start;
        if (this->_size != 0 && this->_size > 0) {
            while (tmp != nullptr) {
                cout << tmp->value.toString() << endl;
                tmp = tmp->next;
            }
        }
    }
    T getByPosition(int pos) {
        if (pos < 0 || pos > _size) throw "Invalid position";
        if (pos == 0) {
            Node* aux = this->_start;
            return aux->value;
        }
        if (pos == _size) {
            Node* aux = this->_end;
            return aux->value;
        }
        Node* aux = this->_start;
        while (aux != nullptr) {
            if (pos == aux->getData().getPosition()) {
                return aux->getData();
            }
            aux = aux->next;
        }
    }
    void modifyAt(int pos, std::function<void(T&)> modify) {
        if (pos < 0 || pos >= _size) throw "Invalid position";
        Node* aux = this->_start;
        for (size_t i = 0; i < pos; ++i) {
            aux = aux->next;
        }
        modify(aux->value);
    }
    void clear() { //ya funciona
        Node* tmp = _start;
        while (tmp != nullptr) {
            Node* next = tmp->getNext();
            delete tmp;
            tmp = next;
        }
        _start = _end = nullptr;
        _size = 0;
    }
    //BubbleSort
    void bubbleSort(std::function<bool(T, T)> compare) {
        Node* aux = this->_start;
        if (aux == nullptr) throw "Cannot sort an empty list";
        while (aux != this->_end) {
            if (compare(aux->value, aux->next->value)) {
                swap(aux->value, aux->next->value);
                if (aux != this->_start)
                    aux = aux->back;
                continue;
            }
            aux = aux->next;
        }
    }
    //MergeSort
    Node* split(Node* head) {
        Node* fast = head, * slow = head;
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        Node* tmp = slow->next;
        slow->next = nullptr;
        return tmp;
    }
    Node* merge(Node* first, Node* second) {
        if (first == nullptr) return second;
        if (second == nullptr) return first;

        if (first->value.getPrice() < second->value.getPrice()) {
            first->next = merge(first->next, second);
            first->next->back = first;
            first->back = nullptr;
            return first;
        }
        else {
            second->next = merge(first, second->next);
            second->next->back = second;
            second->back = nullptr;
            return second;
        }
    }
    Node* mergeSort(Node* head) {
        if (head == nullptr || head->next == nullptr) return head;
        Node* second = split(head);
        head = mergeSort(head);
        second = mergeSort(second);
        return merge(head, second);
        this->_start = merge(head, second);
    } //Revisar stack overflow
    //Quicksort
    Node* partition(Node* low, Node* high) {// Quicksort Partition
        int pivot = high->value.getPrice();
        Node* i = low->back;
        for (Node* j = low; j != high; j = j->next) {
            if (j->value.getPrice() <= pivot) {
                i = (i == nullptr) ? low : i->next;
                swap(i->value, j->value);
            }
        }
        i = (i == nullptr) ? low : i->next;
        swap(i->value, high->value);
        return i;
    }
    void recursiveQuickSort(Node* low, Node* high) {// Recursive Quicksort 
        if (high != nullptr && low != high && low != high->next) {
            Node* p = partition(low, high);
            recursiveQuickSort(low, p->back);
            recursiveQuickSort(p->next, high);
        }
    }
    void quickSort() { // O(n^2)
        recursiveQuickSort(_start, _end);
    }
    bool isEmpty() {
        return this->_size == 0;
    }
    Node* getHead() {
        if (this->_start != nullptr) { return this->_start; }
        else throw "List is empty";
    }
    size_t size() {return this->_size;}
    void delete_by_value(std::function<bool(T)> search) {//funciona (ya borra) !!
        Node* current = this->_start;
        Node* next = nullptr;
        Node* prev = nullptr;
        while (current != nullptr) {
            next = current->getNext();
            if (search(current->getData())) {
                if (prev == nullptr) {
                    // El nodo a eliminar es el primer nodo (_start)
                    this->_start = next;
                    if (next != nullptr) {
                        next->back = nullptr;
                    }
                }
                else {
                    prev->next = next;
                    if (next != nullptr) {
                        next->back = prev;
                    }
                }
                if (current == this->_end) {
                    // El nodo a eliminar es el último nodo (_end)
                    this->_end = prev;
                }
                delete current;
                --_size;
            }
            else {
                prev = current;
            }
            current = next;
        }
    }
    bool search_by_value(std::function<bool(T)> search) {
        Node* tmp = this->_start;
        while (tmp != nullptr) {
            if (search(tmp->getData())) {
                return true;
            }
            tmp = tmp->getNext();
        }
        return false;
    }
    T return_by_value(std::function<bool(T)> search) {
        if (search_by_value(search)) {
            Node* tmp = this->_start;
            while (tmp != nullptr) {
                if (search(tmp->getData())) {
                    return tmp->getData();
                }
                tmp = tmp->getNext();
            }
        }
        throw invalid_argument("Code not found");
    }
};

#endif 