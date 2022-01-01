#include <iostream>

#include "models/Unit.h"
#include "models/Facility.h"

int main() {
    std::cout << "Hello, AtValue!" << std::endl;

    auto facility = make_unique<Facility>();
    try {
        facility->addRoot(new Unit(0, "Root"));
        facility->addUnit(new Unit(1, "Unit 1"), 0);
        facility->addUnit(new Unit(2, "Unit 0"), 0);
    } catch (unsigned e){
        cout << "Parent with id " <<  e << " not found.  Corresponding unit not added to facility. " << endl;
    };

    std::cout << facility->unitCount() << std::endl;
    std::cout << facility->unitCount() << std::endl;

    return 0;
}
