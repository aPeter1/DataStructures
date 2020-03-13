#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <string>
#include <sstream>

template<typename value_type>
    struct Node 
    {
        Node(){}
        Node(value_type value, 
             Node<value_type>* left = NULL, 
             Node<value_type>* right = NULL) : 
             value(value), left_node(left), right_node(right) {}

        std::string toString();

        ~Node(){}
        
        value_type value;
        Node<value_type>* left_node;
        Node<value_type>* right_node;
    };

#endif

template<typename value_type>
    std::string Node<value_type>::toString()
    {
        std::ostringstream output;
        output << value;
        return output.str();
    }