#include <iostream>

#include "models/Unit.h"
#include "models/Facility.h"
#include "utilities/CsvReader.h"

int main() {
    std::cout << "Hello, AtValue!" << std::endl;

    auto station = CsvReader::readCsv("/Users/paul/Repos/tree/data/model_1.csv", true);
    auto failure_modes = CsvReader::readCsv("/Users/paul/Repos/tree/data/failure_modes.csv", true);

    auto facility = make_unique<Facility>();

    try {
        facility->addRoot(std::make_unique<Unit>(0, "Root"));
        facility->addUnit(std::make_unique<Unit>(2, "Test Unit 2"), 0);
        facility->addUnit(std::make_unique<Unit>(1, "Test Unit 1"), 0);
    } catch (unsigned e){
        cout << "Parent with id " <<  e << " not found.  Corresponding unit not added to facility. " << endl;
    };

    std::cout << facility->unitCount() << std::endl;

    return 0;
}
