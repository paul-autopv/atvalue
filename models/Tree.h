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
    shared_ptr<Node<T>> root;
    std::map<unsigned, std::weak_ptr<T>> tree_map;

public:
    const shared_ptr<Node<T>> &getRoot() const;
    void addNode(T &data);

};

template<typename T>
void Tree<T>::addNode(T &data) {
    this->root = std::make_shared<Node<T>>(data);
}

template<typename T>
const shared_ptr<Node<T>> &Tree<T>::getRoot() const {
    return root;
}


#endif //TREE_TREE_H
