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
    map<unsigned, Unit> unit_map_;

    Unit getParent(unsigned id);

public:
    void addUnit(unsigned id, const shared_ptr<Unit>& unit, unsigned parent_id);
    void addRoot(const shared_ptr<Unit>& unit);

    unsigned unitCount() const;
    Unit getNode(unsigned id) const;

};


#endif //TREE_FACILITY_H
