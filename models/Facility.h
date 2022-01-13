//
// Created by Paul on 2021/12/31.
//

#ifndef TREE_FACILITY_H
#define TREE_FACILITY_H

#include <memory>
#include <map>
#include <unordered_map>
#include <iostream>

#include "Unit.h"
#include "CsvMap.h"

using namespace std;

class Facility {
    unordered_map<int, shared_ptr<Unit>> unit_map_;

    void addRoot(unique_ptr<Unit> unit);

    void addUnit(std::unique_ptr<Unit> unit, int parent_id);

    int getParentIdOfUnit(int unit_id) const;

    unsigned getChildrenCountForUnit(int unit_id) const;

    shared_ptr<Unit> registerUnit(unique_ptr<Unit> &unit);

    shared_ptr<Unit> getParent(int parent_id);

    bool isInUnitMap(int id) const;

public:

    void buildFacility(const std::map<unsigned int, std::vector<std::string>>& unit_map);

    unsigned unitCount() const;


};


#endif //TREE_FACILITY_H
