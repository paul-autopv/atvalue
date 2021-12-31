#include <iostream>
#include "models/Unit.h"
#include "models/Facility.h"

int main() {
    std::cout << "Hello, AtValue!" << std::endl;

    auto facility = Facility();
    facility.addRoot(std::make_shared<Unit>(0, "Root"));


    return 0;
}
