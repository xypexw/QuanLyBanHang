#pragma once
#include <iostream>
using namespace std;
template<typename T>
class Stack{
private:
    struct Node {
        T data;
        Node* next;
        Node(T data, Node* next = NULL) : data(data), next(next) {}
    };

    Node* top;

public:
    Stack() : top(NULL) {}
    ~Stack() {}
    void push(T val){
        top = new Node(val, top);
    }
    T pop(){
        if (isEmpty()){
            cout<<"Stack underflow";
            return T();
        }
        Node* tmp = top;
        T val = top->data;
        top = top->next;
        delete tmp;
        return val;
    }

    bool isEmpty() const{
        return top == NULL;
    }
};
