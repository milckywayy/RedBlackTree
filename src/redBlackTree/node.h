#ifndef RED_BLACK_NODE_H
#define RED_BLACK_NODE_H

#include <cstddef>

using namespace std;


enum COLOR {RED, BLACK};

template <typename K, typename V> class Node {
private:
    K key;
    V value;
    COLOR color;

    Node<K, V> *parent;
    Node<K, V> *left;
    Node<K, V> *right;

public:
    Node<K, V>() {
        color = BLACK;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    Node<K, V>(K key, V value) : key(key), value(value) {
        color = RED;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    K getKey() {
        return key;
    }

    V getValue() {
        return value;
    }

    COLOR getColor() {
        return color;
    }

    Node<K, V> *getParent() {
        return parent;
    }

    Node<K, V> *getLeft() {
        return left;
    }

    Node<K, V> *getRight() {
        return right;
    }

    void setKey(K key) {
        this->key = key;
    }

    void setValue(V value) {
        this->value = value;
    }

    void setColor(COLOR color) {
        this->color = color;
    }

    void setParent(Node<K, V> *node) {
        this->parent = node;
    }

    void setLeft(Node<K, V> *node) {
        left = node;
    }

    void setRight(Node<K, V> *node) {
        right = node;
    }

    ~Node() {
    }
};

#endif