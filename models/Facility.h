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
    map<unsigned, shared_ptr<Unit>> unit_map_;

public:
    void addUnit(unsigned id, Unit *unit, unsigned parent_id);
    void addRoot(Unit *unit);

    unsigned unitCount() const;
    int getParentIdOfUnit(int unit_id) const;

};


#endif //TREE_FACILITY_H
