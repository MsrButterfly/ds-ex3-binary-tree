//
//  main.cpp
//  ds-ex3-tree
//
//  Created by Darren Liu on 13-11-27.
//  Copyright (c) 2013年 Darren Liu. All rights reserved.
//

#include <iostream>
#include "include/binary-tree.h"

void print(char &data);

int main(int argc, const char * argv[])
{
    BinaryTree<char> tree;
    BinaryTree<char>::Position root = BinaryTree<char>::Position::Root();
    
    // for (int i = 0; i < 63; i++, root.goNext()) {
    //     tree.addData(root, 'A' + i);
    // }
    // tree.addData(root.left().right().right().right().right().right(), '*');
    tree.addData(root, '*');
    tree.addData(root.left(), '*');
    tree.addData(root.left().right(), '*');
    tree.addData(root.left().right().right(), '*');
    tree.addData(root.left().right().right().right(), '*');
    tree.addData(root.left().right().right().right().right(), '*');
    tree.addData(root.left().right().right().right().right().left(), '*');
    std::cout << tree;
    
    std::cout << "    Recursive Pre  Order: ";
    tree.traversal(BinaryTree<char>::PreOrder, BinaryTree<char>::Recursive, print);
    std::cout << ENDLINE;
    
    std::cout << "    Recursive In   Order: ";
    tree.traversal(BinaryTree<char>::InOrder, BinaryTree<char>::Recursive, print);
    std::cout << ENDLINE;
    
    std::cout << "    Recursive Post Order: ";
    tree.traversal(BinaryTree<char>::PostOrder, BinaryTree<char>::Recursive, print);
    std::cout << ENDLINE;
    
    std::cout << "Non-Recursive Pre  Order: ";
    tree.traversal(BinaryTree<char>::PreOrder, BinaryTree<char>::NonRecursive, print);
    std::cout << ENDLINE;
    
    std::cout << "Non-Recursive In   Order: ";
    tree.traversal(BinaryTree<char>::InOrder, BinaryTree<char>::NonRecursive, print);
    std::cout << ENDLINE;
    
    std::cout << "Non-Recursive Post Order: ";
    tree.traversal(BinaryTree<char>::PostOrder, BinaryTree<char>::NonRecursive, print);
    std::cout << ENDLINE;
    
    tree.swapPosition();
    
    std::cout << tree;
    
    std::cout << "    Recursive Pre  Order: ";
    tree.traversal(BinaryTree<char>::PreOrder, BinaryTree<char>::Recursive, print);
    std::cout << ENDLINE;
    
    std::cout << "    Recursive In   Order: ";
    tree.traversal(BinaryTree<char>::InOrder, BinaryTree<char>::Recursive, print);
    std::cout << ENDLINE;
    
    std::cout << "    Recursive Post Order: ";
    tree.traversal(BinaryTree<char>::PostOrder, BinaryTree<char>::Recursive, print);
    std::cout << ENDLINE;
    
    std::cout << "Non-Recursive Pre  Order: ";
    tree.traversal(BinaryTree<char>::PreOrder, BinaryTree<char>::NonRecursive, print);
    std::cout << ENDLINE;
    
    std::cout << "Non-Recursive In   Order: ";
    tree.traversal(BinaryTree<char>::InOrder, BinaryTree<char>::NonRecursive, print);
    std::cout << ENDLINE;
    
    std::cout << "Non-Recursive Post Order: ";
    tree.traversal(BinaryTree<char>::PostOrder, BinaryTree<char>::NonRecursive, print);
    std::cout << ENDLINE;
    
    return 0;
}

void print(char &data) {
    std::cout << data;
}
