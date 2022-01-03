//
// Created by Paul on 2021/12/31.
//

#include "Facility.h"
§
template <typename First, typename ... Rest>
void Facility::addUnit(First parent_id, Rest ... args) {
    auto unit_ptr = make_shared<Unit>(args...);
    auto parent_ptr = make_shared<Unit>(getParent(parent_id));
    unit_ptr->setParent(parent_ptr);
    parent_ptr->addChild(unit_ptr);
    unit_map_.emplace(unit_ptr->getId(), unit_ptr);
}

shared_ptr<Unit> Facility::getParent(int parent_id) {
    if (!isInUnitMap(parent_id)) {
        std::string message = "Current unit map does not contain unit with provide parent_id";
        throw std::invalid_argument(message);
    }
    return {unit_map_.at(parent_id)};
}


void Facility::addRoot(Unit *unit) {
    unit_map_.emplace(0, std::shared_ptr<Unit>(unit));
}


unsigned Facility::unitCount() const {
    return unit_map_.size();
}

int Facility::getParentIdOfUnit(int unit_id) const {
    if(!isInUnitMap(unit_id)){
        std::string message = "Current unit map does not contain unit with provided id ";
        throw std::invalid_argument(message);
    }
    return unit_map_.at(unit_id)->getParentId();
}

unsigned Facility::getChildrenCountForUnit(int unit_id) const {
    if(!isInUnitMap(unit_id)){
        std::string message = "Current unit map does not contain unit with provided id";
        throw std::invalid_argument(message);
    }    return unit_map_.at(unit_id)->countOfChildren();
}

bool Facility::isInUnitMap(int id) const{
    return unit_map_.find(id) != unit_map_.end();
}
