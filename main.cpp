#include <iostream>

#include "models/Unit.h"
#include "models/Facility.h"

int main() {
    std::cout << "Hello, AtValue!" << std::endl;

    auto facility = make_unique<Facility>();
    facility->addRoot(std::make_shared<Unit>(0, "Root"));
    facility->addUnit(1, make_shared<Unit>(1, "Unit 1"), 0);
    facility->addUnit(2, make_shared<Unit>(2, "Unit 2"), 1);

    std::cout << facility->unitCount() << std::endl;
    auto node = facility->getNode(0);
    cout <<node.isRoot() << endl;
    std::cout << facility->unitCount() << std::endl;

    return 0;
}
