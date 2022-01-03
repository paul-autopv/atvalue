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
//        facility->addRoot(new Unit(0, "Root"));
        auto unit_id {1};
        auto unit_name {"Unit 1"};
        facility->addUnit(0, unit_id, unit_name);
//        facility->addUnit(new Unit(2, "Unit 0"), 1);
    } catch (unsigned e){
        cout << "Parent with id " <<  e << " not found.  Corresponding unit not added to facility. " << endl;
    };

    std::cout << facility->unitCount() << std::endl;

    return 0;
}
