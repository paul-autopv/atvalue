#include <iostream>

#include "models/Unit.h"
#include "models/Facility.h"
#include "utilities/CsvReader.h"
#include "models/CsvMap.h"

int main() {
    std::cout << "Hello, AtValue!" << std::endl;

    StationFields fields;
    auto station = CsvReader::readCsv("/Users/paul/Repos/tree/data/model_1.csv", true);
    auto children_map = std::move(CsvReader::childCounter(station));
    auto failure_modes = CsvReader::readCsv("/Users/paul/Repos/tree/data/failure_modes.csv", true);

    auto facility = make_unique<Facility>();

    auto root = cbegin(station)->second;
    facility->addRoot(std::make_unique<Unit>(stoi(root[0]), root[2]));

    auto cstart = ++cbegin(station);
    for (auto iter { cstart }; iter != cend(station); ++iter) {
        auto id = stoi(iter->second[fields.id]);
        auto name = iter->second[fields.name];
        auto parent_id = stoi(iter->second[fields.parent_id]);
        facility->addUnit(make_unique<Unit>(id, name), parent_id);
    }

//    try {
//        facility->addRoot(std::make_unique<Unit>(0, "Root"));
//        facility->addUnit(std::make_unique<Unit>(2, "Test Unit 2"), 0);
//        facility->addUnit(std::make_unique<Unit>(1, "Test Unit 1"), 0);
//    } catch (unsigned e){
//        cout << "Parent with id " <<  e << " not found.  Corresponding unit not added to facility. " << endl;
//    };

    std::cout << facility->unitCount() << std::endl;

    return 0;
}
