#include <iostream>
#include "bst.h"

int main(int argc, char **argv)
{
    BST bTree = BST();

    std::cout << "We have a tree!" << std::endl;

    bTree.traverseTree();
    bTree.traverseTree("PRE");
    bTree.traverseTree("POST");

    return 0;
};