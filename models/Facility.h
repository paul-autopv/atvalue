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
#include "../probabilities/WeibullProbability.h"

using namespace std;

using FamilyTree = std::shared_ptr<std::map<unsigned int, unsigned int>>;
using InputMap = std::map<unsigned int, std::vector<std::string>>;
using UnitFailureModes = std::unordered_map<unsigned, std::vector<unsigned>>;

class Facility {
    unordered_map<int, shared_ptr<Unit>> unit_map_;

    void addUnit(unique_ptr<Unit> unit, int parent_id);

    void loadUnit(const vector<string>& unit, const InputMap &unit_map, FamilyTree &family_tree, bool isRoot);

    static FamilyTree childCounter(const InputMap& unit_map);

    static unsigned int childrenCount(const FamilyTree & family_tree, unsigned unit_id);

    static std::unique_ptr<UnitFailureModes> unitFailureModes(const InputMap& failure_mode_map);

    int getParentIdOfUnit(int unit_id) const;

    unsigned getChildrenCountForUnit(int unit_id) const;

    shared_ptr<Unit> registerUnit(unique_ptr<Unit> &unit);

    shared_ptr<Unit> getParent(int parent_id);

    bool isInUnitMap(int id) const;


public:

    void buildFacility(const InputMap &unit_map, const InputMap &failure_map);

    unsigned unitCount() const;

    unique_ptr<IProbability> getProbability(const FailureModes &fields, const vector<string> &failure_mode,
                                const basic_string<char, char_traits<char>, allocator<char>> &probability_type) const;
};


#endif //TREE_FACILITY_H
