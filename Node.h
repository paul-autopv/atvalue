//
// Created by Paul on 2021/12/28.
//

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Node {
    weak_ptr<Node<T>> parent;
    vector<shared_ptr<Node<T>>> children;
    unique_ptr<T> data;

public:
    Node();
    explicit Node(T &data);
    Node(weak_ptr<Node<T>> parent, T &data);

    const unique_ptr<T> &getData() const;
};

template<typename T>
Node<T>::Node(weak_ptr<Node<T>> parent, T &data) : parent {parent}, data {make_unique<T>(data)}{

}

template<typename T>
Node<T>::Node(T &data) : data {make_unique<T>(data) } {

}

template<typename T>
const unique_ptr<T> &Node<T>::getData() const {
    return data;
}

template<typename T>
Node<T>::Node() = default;

#endif //TREE_NODE_H
