#include <iostream>

#include "models/Facility.h"
#include "utilities/CsvReader.h"
#include "controllers/Simulator.h"

int main() {
    std::cout << "Hello, AtValue!" << std::endl;

    auto failure_modes = CsvReader::readCsv("/Users/paul/Repos/tree/data/failure_modes.csv", true);
    auto station = CsvReader::readCsv("/Users/paul/Repos/tree/data/model_1.csv", true);

    auto facility = make_unique<Facility>();
    facility->buildFacility(station, failure_modes);

    auto simulator = Simulator(1000, move(facility));
    simulator.run();

    return 0;
}
