#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Stack {
private:
    class Node {
    private:
        T _data;
        Node* _pNext;
    public:
        Node(T data, Node* next = NULL) : _data(data), _pNext(next) {}
        friend Stack;
    };

    Node* top;

public:
    Stack() : top(NULL) {}
    
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const T& val) {
        top = new Node(val, top);
    }

    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack underflow");
        }
        Node* tmp = top;
        T val = top->_data;
        top = top->_pNext;
        delete tmp;
        return val;
    }

    bool isEmpty() const {
        return top == NULL;
    }
};
