#include <iostream>
#include "redBlackTree/redBlackTree.h"

using namespace std;


int main() {
    RedBlackTree<int, int> *tree = new RedBlackTree<int, int>();

    tree->insert(50 , 1);
    tree->print();
    tree->insert(40 , 1);
    tree->print();
    tree->insert(10 , 1);
    tree->print();
    tree->insert(30 , 1);
    tree->print();
    tree->insert(20 , 1);
    tree->print();
    tree->insert(80 , 1);
    tree->print();
    tree->insert(90 , 1);
    tree->print();
    tree->insert(70 , 1);
    tree->print();
    tree->insert(45 , 1);
    
    tree->print();

    delete tree;

    return 0;
}