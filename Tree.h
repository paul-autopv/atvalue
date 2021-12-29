//
// Created by Paul on 2021/12/28.
//

#ifndef TREE_TREE_H
#define TREE_TREE_H


#include <map>
#include "Node.h"

using namespace std;

template <typename T>
class Tree {
private:
    unique_ptr<Node<T>> root;
    std::map<unsigned, std::weak_ptr<T>> tree_map;

public:
    const unique_ptr<Node<T>> &getRoot() const;
    void addRoot(T &data);

};

template<typename T>
void Tree<T>::addRoot(T &data) {
    this->root = std::make_unique<Node<T>>(data);
}

template<typename T>
const unique_ptr<Node<T>> &Tree<T>::getRoot() const {
    return root;
}


#endif //TREE_TREE_H
