//
// Created by Paul on 2021/12/28.
//

#include <iostream>
#include <utility>
#include "Unit.h"

Unit::Unit(int id, std::string name) : id_ {id}, name_ {std::move(name)}, capacity_ {0}{

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
    children_.push_back(weak_ptr<Unit>(child));
}

bool Unit::isRoot() const {
    return parent_.use_count() == 0;
}

void Unit::setParent(const shared_ptr<Unit>& parent_ptr) {
    cout << "Before parent set count is: " << parent_ptr.use_count() << endl;
    parent_ = parent_ptr;
    cout << "After parent set count is: " << parent_ptr.use_count() << endl;
}

int Unit::getParentId() const {
    return parent_->getId();
}

unsigned Unit::countOfChildren() const{
    return children_.size();
}

void Unit::addFailureMode(FailureMode mode) {
    failure_modes_.push_back(mode);

}

double Unit::getCapacity() const {
    return capacity_;
}

void Unit::setCapacity(double capacity) {
    Unit::capacity_ = capacity;
}
