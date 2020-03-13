#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include "node.h"

template<typename value_type>
    class Tree
    {
        public:
            Tree() : root_node(NULL){};
            Tree(Node<value_type>* new_root) : root_node(new_root){}
            Tree(value_type data, Tree<value_type>& left_tree, Tree<value_type>& right_tree) {}

            Tree<value_type> getLeftTree() {return Tree<value_type>(root_node->left_node); }
            Tree<value_type> getRightTree() {return Tree<value_type>(root_node->right_node); }
            value_type getData() {return root_node->value; }

            bool isLeaf() const {return (root_node->left_node == NULL && root_node->right_node == NULL); }
            bool isEmpty() const {return (root_node == NULL); }
            std::string toString();       

            virtual ~Tree() {}
        private:
            Node<value_type>* root_node;
    };

#endif