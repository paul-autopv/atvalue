//
// Created by Paul on 2021/12/31.
//

#ifndef TREE_FACILITY_H
#define TREE_FACILITY_H

#include <memory>
#include <map>

#include "Unit.h"

using namespace std;

class Facility {
    map<int, shared_ptr<Unit>> unit_map_;

    shared_ptr<Unit> registerUnit(unique_ptr<Unit> &unit);

    shared_ptr<Unit> getParent(int parent_id);

    bool isInUnitMap(int id) const;


public:

    void addUnit(std::unique_ptr<Unit> unit, int parent_id);

    void addRoot(unique_ptr<Unit> unit);

    unsigned unitCount() const;

    int getParentIdOfUnit(int unit_id) const;

    unsigned getChildrenCountForUnit(int unit_id) const;
};


#endif //TREE_FACILITY_H
