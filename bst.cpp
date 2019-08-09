#include "bst.h"

void BST::addNode(int value)
{
    if (root_node == nullptr)
    {
        root_node = new Node(value);
    }
}

void BST::traverseTree(std::string method)
{
    if(method == "PRE")
    {
        std::cout << "Pre-order Tree Traversal" << std::endl;
        normalTraversal(root_node);
    }
    else if(method == "POST")
    {
        std::cout << "Post-order Tree Traversal" << std::endl;
        postOrderTraversal(root_node);
    }
    else
    {
        std::cout << "Normal Tree Traversal" << std::endl;
        normalTraversal(root_node);
    }
}

void BST::normalTraversal(Node* node)
{
    if(node == nullptr)
    {
        return;
    }

    normalTraversal(node->getLeft());
    std::cout << node->toString() << std::endl;
    normalTraversal(node->getRight());
}

void BST::preOrderTraversal(Node* node)
{
    if(node == nullptr)
    {
        return;
    }

    std::cout << node->toString() << std::endl;
    normalTraversal(node->getLeft());
    normalTraversal(node->getRight());
}

void BST::postOrderTraversal(Node* node)
{
    if(node == nullptr)
    {
        return;
    }

    normalTraversal(node->getLeft());
    normalTraversal(node->getRight());
    std::cout << node->toString() << std::endl;
}