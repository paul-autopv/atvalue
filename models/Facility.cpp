//

#include "Facility.h"



//
// Created by Paul on 2021/12/31.
void Facility::buildFacility(const UnitMap& unit_map) {
    auto family_tree= childCounter(unit_map);

    auto root = cbegin(unit_map)->second;
    configureUnit(root, unit_map, family_tree, true);

    auto cstart = ++cbegin(unit_map);
    for (auto iter { cstart }; iter != cend(unit_map); ++iter) {
        auto unit = iter->second;
        configureUnit(unit, unit_map, family_tree, false);
    }
}

FamilyTree Facility::childCounter(const UnitMap& unit_map) {

    StationFields fields;
    auto children = std::make_unique<std::map<unsigned, unsigned>>();

    if (!unit_map.empty()) {
        for (auto iter{cbegin(unit_map)}; iter != cend(unit_map); ++iter) {
            auto parent_id = stoi(iter->second[fields.parent_id]);
            if (children == nullptr || children->find(parent_id) == children->end())
                (*children)[parent_id] = 0;
            (*children)[parent_id]++;
        }
    }
    return children;
}

void Facility::configureUnit(const vector<string>& unit, const UnitMap &unit_map, FamilyTree &family_tree, bool isRoot) {

    StationFields fields;

    auto id = stoi(unit[fields.id]);
    auto name = unit[fields.name];
    auto capacity = stod(unit[fields.capacity]);
    auto children = childrenCount(family_tree, id);
    auto parent_id = (isRoot) ? -1 : stoi(unit[fields.parent_id]);
    addUnit(make_unique<Unit>(id, name, capacity, children), parent_id);

    cout << "Added " << name << " (id: " << id << ")" << endl;
}

void Facility::addUnit(std::unique_ptr<Unit> unit, int parent_id) {
    auto unit_ptr = registerUnit(unit);

    if (parent_id > 0){
        auto parent_ptr = getParent(parent_id);
        unit_ptr->setParent(weak_ptr<Unit>(parent_ptr));
        parent_ptr->addChild(unit_ptr);
    }
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

unsigned int Facility::childrenCount(const FamilyTree& family_tree, unsigned int unit_id) {
    if (!family_tree->empty() && (*family_tree)[unit_id]){
        return family_tree->find(unit_id)->second;
    }
    return 0;
}
