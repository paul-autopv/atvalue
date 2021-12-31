//
// Created by Paul on 2021/12/31.
//

#include <iostream>
#include "Facility.h"

void Facility::addUnit(unsigned id, const shared_ptr<Unit>& unit, unsigned parent_id) {
    auto parent = make_shared<Unit>(getParent(parent_id));
    unit->setParent(parent);
    unit_map_.emplace(id, *unit);
}

void Facility::addRoot(const shared_ptr<Unit>& unit) {
    unit_map_.emplace(0, *unit);
}

unsigned Facility::unitCount() const {
    return unit_map_.size();
}

Unit Facility::getNode(unsigned id) const {
    return unit_map_.at(id);
}

Unit Facility::getParent(unsigned id) {
    if (unit_map_.find(id) == unit_map_.end())
        throw "Parent unit not found.";
    return unit_map_.at(id);

}
