#include <iostream>

#include "models/Unit.h"
#include "models/Facility.h"
#include "utilities/CsvReader.h"
#include "models/CsvMap.h"

int main() {
    std::cout << "Hello, AtValue!" << std::endl;

    StationFields fields;
    auto failure_modes = CsvReader::readCsv("/Users/paul/Repos/tree/data/failure_modes.csv", true);

    auto facility = make_unique<Facility>();
    auto station = CsvReader::readCsv("/Users/paul/Repos/tree/data/model_1.csv", true);
    auto children_map = std::move(CsvReader::childCounter(station));
    facility->buildFacility(station);

    std::cout << facility->unitCount() << std::endl;

    return 0;
}
