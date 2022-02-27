#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by Paul on 2021/12/28.
//

#include <iostream>
#include <utility>
#include "Component.h"

Component::Component(int id, string name, const int &duration, int days_installed,
                     vector<shared_ptr<FailureMode>> failure_modes, double capacity, int children) :
        id_ {id},
        name_ {std::move(name)},
        duration_ {duration},
        failure_modes_ {move(failure_modes)},
        capacity_ {capacity},
        day_installed_ {days_installed}{
    children_.reserve(children);
    available_days.resize(duration_, true);
    online_days.resize(duration_, true);
};


std::ostream &operator<<(std::ostream &os, const Component &unit) {
    os << "Component id_: " << unit.id_ << " (" << unit.name_ << ")";
    return os;
}

int Component::getId() const{
    return this->id_;
}

void Component::addChild(const shared_ptr<Component>& child) {
    children_.push_back(child);
}

void Component::setParent(const shared_ptr<Component>& parent_ptr) {
    parent_ = weak_ptr<Component>(parent_ptr);
}

int Component::getParentId() const {
    return parent_.lock()->getId();
}

void Component::setDayInstalled(const int& day) {
    day_installed_ = day;
}

void Component::scheduleOutage(const int &start, const int &outage_duration) {
    auto end = outage_duration < 0 ? start : min(start + outage_duration, duration_);
    for (auto day = start; day < end; ++day){
        online_days.at(day) = false;
        available_days.at(day) = false;
    }
    if (!children_.empty()) {
        for (auto &child: children_) {
            child->scheduleOutage(start, outage_duration);
        }
    }
}

bool Component::isOnline(const int &day) const {
    return online_days.at(day);
}

bool Component::isAvailable(const int &day) const {
    return available_days.at(day);
}

vector<bool> Component::getAvailability() {
    return available_days;
}

#pragma clang diagnostic pop