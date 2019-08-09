#ifndef BST_H_
#define BST_H_

#include <iostream>
#include "node.h"

class BST
{
    public:
        BST(){}
        void traverseTree(std::string method = std::string());
        void addNode(int value);
        void removeNode(int value);
        void balanceTree();

    private:
        Node* root_node = nullptr;

        void preOrderTraversal(Node* node);
        void postOrderTraversal(Node* node);
        void normalTraversal(Node* node);
};

#endif