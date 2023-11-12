#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "node.h"
#include "string"
#include "iostream"

using namespace std;


template<typename K, typename V> class RedBlackTree {
private:
    Node<K, V> *root;
    int n;

    Node<K, V> *NIL;
    
public:
    RedBlackTree() {
        NIL = new Node<K, V>();
        root = NIL;
        n = 0;
    }

    void insert(K key, V value) {
        Node<K, V> *node;
        Node<K, V> *pointer = root;

        // Case when tree is empty
        if (root == NIL) {
            node = new Node<K, V>(key, value);
            node->setParent(NIL);
            node->setLeft(NIL);
            node->setRight(NIL);
            node->setColor(BLACK);
            root = node;
            n++;

            return;
        }

        while (true) {
            if (key == pointer->getKey()) {
                return; // Key already exist
            }
            else if (key < pointer->getKey()) {
                if (pointer->getLeft() == NIL) {
                    node = new Node<K, V>(key, value);
                    node->setParent(NIL);
                    node->setLeft(NIL);
                    node->setRight(NIL);
                    node->setParent(pointer);
                    pointer->setLeft(node);
                    n++;

                    break;
                }
                pointer = pointer->getLeft();
            }
            else {
                if (pointer->getRight() == NIL) {
                    node = new Node<K, V>(key, value);
                    node->setParent(NIL);
                    node->setLeft(NIL);
                    node->setRight(NIL);
                    node->setParent(pointer);
                    pointer->setRight(node);
                    n++;

                    break;
                }
                pointer = pointer->getRight();
            }
        }

        insertFix(node);
    }

    void remove(K key) {
        Node<K, V> *z = findNode(key);
        Node<K, V> *y;
        Node<K, V> *x;

        if (z == NIL) {
            return; // Node not found
        }

        if (z->getLeft() == NIL || z->getRight() == NIL) {
            y = z;
        }
        else {
            y = findSuccessor(z);
        }

        if (y->getLeft() != NIL) {
            x = y->getLeft();
        }
        else {
            x = y->getRight();
        }

        x->setParent(y->getParent());

        if (y->getParent() == NIL) {
            root = x;
        }
        else if (y == y->getParent()->getLeft()) {
            y->getParent()->setLeft(x);
        }
        else {
            y->getParent()->setRight(x);
        }

        if (y != z) {
            z->setKey(y->getKey());
            z->setValue(y->getValue());
        }

        if (isBlack(y)) {
            removeFix(x);
        }

        delete y;
    }

    V get(K key) {
        Node<K, V> *node = findNode(key);

        if (node != NIL) {
            return node->getValue();
        }
        else {
            throw runtime_error("No such key in RBTree.");
        }
    }

    int size () {
        return n;
    }

    void print() {
        if (root != NIL) {
            printHelper(root, "", true);
        }
    }

    ~RedBlackTree() {
        if (root != NIL) {
            freeNodes(root);
        }

        delete NIL;
    }

private:
    void rotateLeft(Node<K, V> *x) {
        Node<K, V> *y = x->getRight();

        x->setRight(y->getLeft());
        if (y->getLeft() != NIL) {
            y->getLeft()->setParent(x);
        }

        y->setParent(x->getParent());
        if (x->getParent() == NIL) {
            root = y;
        }
        else if (x == x->getParent()->getLeft()) {
            x->getParent()->setLeft(y);
        }
        else {
            x->getParent()->setRight(y);
        }

        y->setLeft(x);
        x->setParent(y);
    }

    void rotateRight(Node<K, V> *x) {
        Node<K, V> *y = x->getLeft();

        x->setLeft(y->getRight());
        if (y->getRight() != NIL) {
            y->getRight()->setParent(x);
        }

        y->setParent(x->getParent());
        if (x->getParent() == NIL) {
            root = y;
        }
        else if (x == x->getParent()->getRight()) {
            x->getParent()->setRight(y);
        }
        else {
            x->getParent()->setLeft(y);
        }

        y->setRight(x);
        x->setParent(y);
    }

    void insertFix(Node<K, V> *x) {
        Node<K, V> *y;

        while (x != root && isRed(x) && isRed(x->getParent())) {
            if (x->getParent() == x->getParent()->getParent()->getLeft()) {
                // Left
                y = x->getParent()->getParent()->getRight();

                // Case 1
                if (isRed(y)) {
                    y->setColor(BLACK);
                    x->getParent()->setColor(BLACK);
                    x->getParent()->getParent()->setColor(RED);

                    x = x->getParent()->getParent();
                }
                else {
                    // Case 2
                    if (x == x->getParent()->getRight()) {
                        x = x->getParent();
                        rotateLeft(x);
                    }
                    // Case 3
                    x->getParent()->setColor(BLACK);
                    x->getParent()->getParent()->setColor(RED);
                    rotateRight(x->getParent()->getParent());
                }
            }
            else {
                // Right
                y = x->getParent()->getParent()->getLeft();

                // Case 1
                if (isRed(y)) {
                    y->setColor(BLACK);
                    x->getParent()->setColor(BLACK);
                    x->getParent()->getParent()->setColor(RED);

                    x = x->getParent()->getParent();
                }
                else {
                    // Case 2
                    if (x == x->getParent()->getLeft()) {
                        x = x->getParent();
                        rotateRight(x);
                    }
                    // Case 3
                    x->getParent()->setColor(BLACK);
                    x->getParent()->getParent()->setColor(RED);
                    rotateLeft(x->getParent()->getParent());
                }
            }
        }

        root->setColor(BLACK);
    }

    void removeFix(Node<K, V> *x) {
        Node<K, V> *w;

        while (x != root && isBlack(x)) {
            if (x == x->getParent()->getLeft()) {
                w = x->getParent()->getRight();

                // Case 1
                if (isRed(w)) {
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    rotateLeft(x->getParent());
                    w = x->getParent()->getRight();
                }

                // Case 2
                if (isBlack(w->getLeft()) && isBlack(w->getRight())) {
                    w->setColor(RED);
                    x = x->getParent();
                }
                else {
                    // Case 3
                    if (isBlack(w->getRight())) {
                        w->setColor(RED);
                        rotateRight(w);
                        w = x->getParent()->getRight();
                    }

                    // Case 4
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    w->getRight()->setColor(BLACK);
                    rotateLeft(x->getParent());
                    x = root;
                }
            }
            else {
                w = x->getParent()->getLeft();

                // Case 1
                if (isRed(w)) {
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    rotateRight(x->getParent());
                    w = x->getParent()->getLeft();
                }

                // Case 2
                if (isBlack(w->getLeft()) && isBlack(w->getRight())) {
                    w->setColor(RED);
                    x = x->getParent();
                }
                else {
                    // Case 3
                    if (isBlack(w->getLeft())) {
                        w->setColor(RED);
                        rotateLeft(w);
                        w = x->getParent()->getLeft();
                    }

                    // Case 4
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    w->getLeft()->setColor(BLACK);
                    rotateRight(x->getParent());
                    x = root;
                }
            }
        }

        x->setColor(BLACK);
    }

    Node<K, V> *findNode(K key) {
        Node<K, V> *pointer = root;

        while (pointer != NIL && key != pointer->getKey()) {
            if (key < pointer->getKey()) {
                pointer = pointer->getLeft();
            }
            else {
                pointer = pointer->getRight();
            }
        }

        return pointer;
    }

    Node<K, V>* findSuccessor(Node<K, V>* node) {
        if (node == NIL) {
            return NIL;
        }

        if (node->getRight() != NIL) {
            Node<K, V>* current = node->getRight();
            while (current->getLeft() != NIL) {
                current = current->getLeft();
            }
            return current;
        } 
        else {
            Node<K, V>* parentNode = node->getParent();
            while (parentNode != NIL && node == parentNode->getRight()) {
                node = parentNode;
                parentNode = parentNode->getParent();
            }
            return parentNode;
        }
    }

    bool isRed(Node<K, V> *node) {
        if (node == NIL) {
            return false;
        }
        else {
            return node->getColor() == RED;
        }
    }

    bool isBlack(Node<K, V> *node) {
        if (node == NIL) {
            return true;
        }
        else {
            return node->getColor() == BLACK;
        }
    }

    void printHelper(Node<K, V> *node, string indent, bool last) {
        if (node != NIL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }
            
            string sColor = node->getColor() == RED ? "RED" : "BLACK";
            cout << node->getKey() << "(" << sColor << ")" << endl;
            printHelper(node->getLeft(), indent, false);
            printHelper(node->getRight(), indent, true);
        }
    }

    void freeNodes(Node<K, V> *node) {
        if (node == NIL) {
            return;
        }

        freeNodes(node->getLeft());
        freeNodes(node->getRight());
        delete node;
    }
};

#endif