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
    map<unsigned, weak_ptr<Unit>> unit_map_;

public:
    void addUnit(Unit &unit, unsigned parent_id);
    void addRoot(shared_ptr<Unit> unit);

};


#endif //TREE_FACILITY_H
