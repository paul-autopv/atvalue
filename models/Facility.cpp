//
// Created by Paul on 2021/12/31.
//

#include "Facility.h"

void Facility::addRoot(unique_ptr<Unit> unit) {
    registerUnit(unit);
}

void Facility::addUnit(std::unique_ptr<Unit> unit, int parent_id) {
    auto unit_ptr = registerUnit(unit);

    auto parent_ptr = getParent(parent_id);
    unit_ptr->setParent(weak_ptr<Unit>(parent_ptr));

    parent_ptr->addChild(unit_ptr);
}

shared_ptr<Unit> Facility::registerUnit(unique_ptr<Unit> &unit) {
    auto  unit_ptr = shared_ptr<Unit>(move(unit));
    unit_map_.emplace(unit_ptr->getId(), unit_ptr);
    return unit_ptr;
}

shared_ptr<Unit> Facility::getParent(int parent_id) {
    if (!isInUnitMap(parent_id)) {
        std::string message = "Current unit map does not contain unit with parent_id";
        throw std::invalid_argument( message );
    }
    return {unit_map_.at(parent_id)};
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

void Facility::buildFacility(const std::map<unsigned int, std::vector<std::string>>& unit_map) {

    StationFields fields;
    auto root = cbegin(unit_map)->second;
    this->addRoot(std::make_unique<Unit>(stoi(root[fields.id]), root[fields.name]));

    auto cstart = ++cbegin(unit_map);
    for (auto iter { cstart }; iter != cend(unit_map); ++iter) {
        auto id = stoi(iter->second[fields.id]);
        auto name = iter->second[fields.name];
        auto parent_id = stoi(iter->second[fields.parent_id]);
        auto capacity = stod(iter->second[fields.capacity]);
        this->addUnit(make_unique<Unit>(id, name, capacity), parent_id);
        cout << "Added " << name << " (id: " << id << ", parent: " << parent_id << ")" << endl;
    }


}
