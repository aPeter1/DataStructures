#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <string>

class Node 
{
    public:
        Node(){}
        Node(int value):value(value){}

        int getValue() {return value; }
        int setValue(int new_value) {value = new_value; }
        Node* getLeft() {return left_node; }
        Node* getRight() {return right_node; }

        std::string toString();
        
    private:
        int value;
        Node* left_node = nullptr;
        Node* right_node = nullptr;
        Node* parent_node = nullptr;
};

#endif