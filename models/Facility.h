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

    void addUnit(unique_ptr<Unit> unit);

    void addUnit(std::unique_ptr<Unit> unit, int parent_id);

    void configureUnit(const vector<string>& unit, const map<unsigned int, std::vector<std::string>> &unit_map,
                       shared_ptr<std::map<unsigned int, unsigned int>> &family_tree, bool isRoot);

    static std::shared_ptr<std::map<unsigned int, unsigned int>> childCounter(const map<unsigned int, vector<std::string>>& unit_map);

    static unsigned int childrenCount(std::shared_ptr<std::map<unsigned, unsigned>> family_tree, unsigned unit_id);

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
