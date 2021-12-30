#include <iostream>
#include "Unit.h"
#include "Tree.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Tree<Unit> tree;
    auto root = std::make_unique<Unit>(0, "root");

    tree.addNode(*root);

    std::cout << tree.getRoot()->getData()->getName() << std::endl;

    return 0;
}
