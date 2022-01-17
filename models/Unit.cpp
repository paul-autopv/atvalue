//
// Created by Paul on 2021/12/28.
//

#include <iostream>
#include <utility>
#include "Unit.h"

Unit::Unit(int id, string name, int days_installed, vector<shared_ptr<FailureMode>> failure_modes, double capacity, int children)
        : id_ {id}, name_ {std::move(name)}, failure_modes_ {move(failure_modes)}, capacity_ {capacity}, days_installed_ {days_installed}{
    children_.reserve(children);
};

std::ostream &operator<<(std::ostream &os, const Unit &unit) {
    os << "Unit id_: " << unit.id_ << " (" << unit.name_ << ")";
    return os;
}

int Unit::getId() const{
    return this->id_;
}

std::string Unit::getName() const {
    return this->name_;
}

void Unit::addChild(const shared_ptr<Unit>& child) {
    children_.push_back(child);
}

bool Unit::isRoot() const {
    return parent_.use_count() == 0;
}

void Unit::setParent(weak_ptr<Unit> parent_ptr) {
    parent_ = move(parent_ptr);
}

int Unit::getParentId() const {
    return parent_.lock()->getId();
}

int Unit::countOfChildren() const{
    return children_.size();
}

void Unit::addFailureMode(unique_ptr<FailureMode> mode) {
    failure_modes_.push_back(move(mode));

}

double Unit::getCapacity() const {
    return capacity_;
}

int Unit::getDaysInstalled() const {
    return days_installed_;
}

