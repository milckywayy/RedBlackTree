#include <iostream>
#include "redBlackTree/redBlackTree.h"

using namespace std;


int main() {
    RedBlackTree<int, int> *tree = new RedBlackTree<int, int>();

    tree->insert(2, 1);
    tree->insert(3, 1);
    tree->insert(1, 1);
    tree->insert(4, 1);

    tree->print();
    cout << endl;

    tree->remove(1);

    tree->print();

    delete tree;

    return 0;
}