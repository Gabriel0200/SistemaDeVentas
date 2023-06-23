#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <functional>

template<class T>
class MyVector {
    T* arr;
    int current;
    int capacity;
public:
    MyVector() {
        arr = new T[0];
        capacity = 0;
        current = 0;
    }
    ~MyVector() { delete[] arr; }

    void push_back(T e) {
        if (current == capacity) {
            T* temp = new T[2 * capacity + 1];
            for (size_t i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            capacity = 2 * capacity + 1;
            arr = temp;
        }
        arr[current] = e;
        current++;
    }
    void pop_back() {
        if (current > 0) {
            current--;
            if (current < capacity / 2) {
                T* temp = new T[capacity / 2];
                for (int i = 0; i < current; i++) {
                    temp[i] = arr[i];
                }
                delete[] arr;
                capacity /= 2;
                arr = temp;
            }
        }
    }
    void delete_by_price(float price) {
        //if (idx < 0 || idx >= current) {
        //    return;
        //}
        //for (int i = idx; i < current - 1; ++i) {
        //    arr[i] = arr[i + 1];
        //}
        for (int i = 0; i < current-1; i++) {
            if (arr[i - 1] = price) {
                pop_back();
            }
        }
    }
    /*void delete_by_value(T value) { //Esta funcion no funciona todavía
        for (int i = 0; i < current; ++i) {
            if (arr[i] == value) {
                delete_by_index(i + 1);
            }
        }
    }*/
    void clear() {
        delete[] arr;
        current = 0;
        capacity = 0;
        arr = new T[0];
    }
    void print(function<void(T)> f) {
        for (size_t i = 0; i < current; ++i) {
            f(arr[i]);
        }
    }
    int size() {
        return current;
    }
    T getVector(int i) {
        return arr[i];
    }
};

#endif