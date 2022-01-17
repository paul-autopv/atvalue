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
#include "../probabilities/TriangularProbability.h"

using namespace std;

using FamilyTree = std::shared_ptr<std::map<int, int>>;
using InputMap = std::map<int, std::vector<std::string>>;
using UnitFailureModes = std::unordered_map<int, std::vector<int>>;

class Facility {
    unordered_map<int, shared_ptr<Unit>> unit_map_;

    unordered_map<int, shared_ptr<FailureMode>> failure_map_;

    void addUnit(unique_ptr<Unit> unit, int parent_id);

    void loadUnit(const vector<string> &unit, const InputMap &unit_map, FamilyTree &family_tree,
                  vector<shared_ptr<FailureMode>> failures, bool isRoot);

    static FamilyTree childCounter(const InputMap& unit_map);

    static int childrenCount(const FamilyTree & family_tree, int unit_id);

    static unique_ptr<IProbability> getProbability(const vector<string> &failure_mode,
                                                   const basic_string<char, char_traits<char>, allocator<char>> &probability_type) ;

    static std::unique_ptr<UnitFailureModes> unitFailureModes(const InputMap& failure_mode_map);

    int getParentIdOfUnit(int unit_id) const;

    int getChildrenCountForUnit(int unit_id) const;

    shared_ptr<Unit> registerUnit(unique_ptr<Unit> &unit);

    shared_ptr<Unit> getParent(int parent_id);

    static vector<shared_ptr<FailureMode>> getFailureModes(const InputMap &failure_map, vector<int> &unit_failures);

    void registerFailureModes(const vector<shared_ptr<FailureMode>>& failure_modes);

    bool isInUnitMap(int id) const;

public:

    void buildFacility(const InputMap &unit_map, const InputMap &failure_map);

    int unitCount() const;

    int failureCount() const;

};


#endif //TREE_FACILITY_H
