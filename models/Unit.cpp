//
// Created by Paul on 2021/12/28.
//

#include <iostream>
#include <utility>
#include "Unit.h"

Unit::Unit(unsigned int id, std::string name) : id_ {id}, name_ {std::move(name)}{

};

std::ostream &operator<<(std::ostream &os, const Unit &unit) {
    os << "Unit id_: " << unit.id_ << " (" << unit.name_ << ")";
    return os;
}

unsigned Unit::getId() const{
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

void Unit::setParent(const shared_ptr<Unit>& parent_ptr) {
    parent_ = parent_ptr;
    parent_.lock()->addChild(make_shared<Unit>(*this));
}

