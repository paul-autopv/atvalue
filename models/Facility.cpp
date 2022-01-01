//
// Created by Paul on 2021/12/31.
//

#include <iostream>
#include "Facility.h"

void Facility::addUnit(unsigned id, Unit *unit, unsigned parent_id) {
    auto parent = shared_ptr<Unit>(unit_map_.at(parent_id));
    unit->setParent(parent);
    unit_map_.emplace(id, shared_ptr<Unit>(unit));
}

void Facility::addRoot(Unit *unit) {
    unit_map_.emplace(0, std::shared_ptr<Unit>(unit));
}

unsigned Facility::unitCount() const {
    return unit_map_.size();
}

int Facility::getParentIdOfUnit(int unit_id) const {
    return unit_map_.at(unit_id)->getParentId();
}

