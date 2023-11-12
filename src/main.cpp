#include <iostream>
#include "redBlackTree/redBlackTree.h"

using namespace std;


int main() {
    RedBlackTree<int, int> *tree = new RedBlackTree<int, int>();

    tree->insert(50 , 1);
    tree->insert(40 , 2);
    tree->insert(10 , 3);
    tree->insert(30 , 4);
    tree->insert(20 , 5);
    tree->insert(80 , 6);
    tree->insert(90 , 7);
    tree->insert(70 , 8);
    tree->insert(45 , 9);
    
    cout << "50 " << tree->get(50) << endl;
    cout << "20 " << tree->get(20) << endl;
    cout << "45 " << tree->get(45) << endl;
    cout << "10 " << tree->get(10) << endl;
    cout << "90 " << tree->get(90) << endl;

    tree->print();

    delete tree;

    return 0;
}