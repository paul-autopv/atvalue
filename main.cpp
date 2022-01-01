#include <iostream>

#include "models/Unit.h"
#include "models/Facility.h"
#include "utilities/CsvReader.h"

int main() {
    std::cout << "Hello, AtValue!" << std::endl;

    CsvReader reader = CsvReader();
    auto station = reader.readCsv("/Users/paul/Repos/tree/data/model_1.csv", true);
    auto failure_modes = reader.readCsv("/Users/paul/Repos/tree/data/failure_modes.csv", true);

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
