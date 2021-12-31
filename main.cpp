#include <iostream>
#include "models/Unit.h"
#include "models/Tree.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Tree<Unit> tree;
    auto root = std::make_unique<Unit>(0, "root");

    tree.addNode(*root);

    std::cout << tree.getRoot()->getData()->getName() << std::endl;
    std::cout << tree.getRoot()->isRoot() << std::endl;

    return 0;
}
