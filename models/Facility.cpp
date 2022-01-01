//
// Created by Paul on 2021/12/31.
//

#include "Facility.h"

void Facility::addUnit(Unit *unit, int parent_id) {
    auto unit_ptr = shared_ptr<Unit>(unit);
    shared_ptr<Unit> parent_ptr = getParent(parent_id);
    unit->setParent(parent_ptr);
    parent_ptr->addChild(unit_ptr);
    unit_map_.emplace(unit->getId(), unit_ptr);
}

shared_ptr<Unit> Facility::getParent(int parent_id) {
    if (!isInUnitMap(parent_id))
        throw (parent_id);
    return {unit_map_.at(parent_id)};
}

void Facility::addRoot(Unit *unit) {
    unit_map_.emplace(0, std::shared_ptr<Unit>(unit));
}

unsigned Facility::unitCount() const {
    return unit_map_.size();
}

int Facility::getParentIdOfUnit(int unit_id) const {
    if(!isInUnitMap(unit_id))
        throw (unit_id);
    return unit_map_.at(unit_id)->getParentId();
}

unsigned Facility::getChildrenCountForUnit(int unit_id) const {
    if (!isInUnitMap(unit_id))
        throw (unit_id);
    return unit_map_.at(unit_id)->countOfChildren();
}

bool Facility::isInUnitMap(int id) const{
    return unit_map_.find(id) != unit_map_.end();
}
