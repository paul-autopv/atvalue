//
// Created by Paul on 2021/12/28.
//

#include <iostream>
#include <utility>
#include "Component.h"

Component::Component(int id, string name, int days_installed, vector<shared_ptr<FailureMode>> failure_modes, double capacity, int children)
        : id_ {id}, name_ {std::move(name)}, failure_modes_ {move(failure_modes)}, capacity_ {capacity}, days_installed_ {days_installed}{
    children_.reserve(children);
};

std::ostream &operator<<(std::ostream &os, const Component &unit) {
    os << "Component id_: " << unit.id_ << " (" << unit.name_ << ")";
    return os;
}

int Component::getId() const{
    return this->id_;
}

std::string Component::getName() const {
    return this->name_;
}

void Component::addChild(const shared_ptr<Component>& child) {
    children_.push_back(child);
}

bool Component::isRoot() const {
    return parent_.use_count() == 0;
}

void Component::setParent(weak_ptr<Component> parent_ptr) {
    parent_ = move(parent_ptr);
}

int Component::getParentId() const {
    return parent_.lock()->getId();
}

int Component::countOfChildren() const{
    return children_.size();
}

void Component::addFailureMode(unique_ptr<FailureMode> mode) {
    failure_modes_.push_back(move(mode));

}

double Component::getCapacity() const {
    return capacity_;
}

int Component::getDaysInstalled() const {
    return days_installed_;
}

void Component::shutdown(ShutdownCode code) {
    is_online_ = false;
    if (code != ShutdownCode::constrained)
        is_available_ = false;
    for (const auto& child : children_) {
        child->shutdown(code);
    }
}

bool Component::isAvailable() const {
    return is_available_;
}

bool Component::isOnline() const {
    return is_online_;
}
