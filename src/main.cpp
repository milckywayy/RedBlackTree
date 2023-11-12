#include <iostream>
#include <vector>
#include <random>

#include "redBlackTree/redBlackTree.h"

using namespace std;


vector<int> *randomDataGenerator(int count, int min, int max, unsigned int seed) {
    vector<int> *randomNumbers = new vector<int>;
    mt19937 generator(seed);
    uniform_int_distribution<int> distribution(min, max);

    for (int i = 0; i < count; ++i) {
        randomNumbers->push_back(distribution(generator));
    }

    return randomNumbers;
}

int main() {
    RedBlackTree<int, int> *tree = new RedBlackTree<int, int>();

    int size = 10;
    vector<int> *data = randomDataGenerator(size, 0, 99999999, 80085);

    // insert check
    for (int i = 0; i < size; i++) {
        tree->insert(data->at(i), data->at(i));
    }
    cout << "after insert size: " << tree->size() << endl;

    // get check
    int result;
    for (int i = 0; i < size; i++) {
        result = tree->get(data->at(i));
        cout << (result == data->at(i) ? "" : "get failed");
    }
    cout << endl;

    // remove check
    for (int i = 0; i < size; i++) {
        tree->remove(data->at(i));
    }
    cout << "after remove size: " << tree->size() << endl;

    delete tree;
    delete data;

    return 0;
}