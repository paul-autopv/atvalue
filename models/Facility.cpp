//
// Created by Paul on 2021/12/31.
//

#include <iostream>
#include "Facility.h"

void Facility::addUnit(Unit *unit, unsigned parent_id) {
    auto unit_ptr = shared_ptr<Unit>(unit);
    auto parent_ptr = shared_ptr<Unit>(unit_map_.at(parent_id));
    unit->setParent(parent_ptr);
    parent_ptr->addChild(unit_ptr);
    unit_map_.emplace(unit->getId(), unit_ptr);
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

unsigned Facility::getChildrenCountOfUnit(int unit_id) const {
    auto unit = unit_map_.at(unit_id);
    return unit->countOfChildren();
}
