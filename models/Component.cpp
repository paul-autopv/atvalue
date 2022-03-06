#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by Paul on 2021/12/28.
//

#include <iostream>
#include <utility>
#include "Component.h"

Component::Component(int id, string name, const int &simulation_duration, int days_installed,
                     vector<shared_ptr<FailureMode>> failure_modes, double capacity, int children) :
        id_ {id},
        name_ {std::move(name)},
        simulation_duration_ {simulation_duration},
        failure_modes_ {move(failure_modes)},
        active_capacity_ {capacity},
        day_installed_ {days_installed}{
    children_.reserve(children);
    available_days.resize(simulation_duration_, true);
    online_days.resize(simulation_duration_, true);
    capacity_loss_.resize(simulation_duration_, 0);
};

std::ostream &operator<<(std::ostream &os, const Component &unit) {
    os << "Component id_: " << unit.id_ << " (" << unit.name_ << ")";
    return os;
}

int Component::getId() const{
    return this->id_;
}

void Component::addChild(const shared_ptr<Component>& child) {
    if (child->getId() == this->getId())
        throw std::invalid_argument("Trying to add child with same id as parent.");
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
    auto end = outage_duration < 0 ? start : min(start + outage_duration, simulation_duration_);
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

void Component::scheduleCapacityLoss(const int &start, const int &outage_duration) {
    setCapacity(start, outage_duration, getCapacity());
}

void Component::setCapacity(const int &start, const int &outage_duration, const double &value) {
    auto end = outage_duration < 0 ? start : min(start + outage_duration, simulation_duration_);
    for (auto day = start; day < end; ++day) {
        capacity_loss_.at(day) = value;
    }
    // avoid possible double counting of capacity loss
    if (!children_.empty()) {
        for (auto &child: children_) {
            child->setCapacity(start, outage_duration, 0);
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

double Component::getCapacity() {
    if (active_capacity_ > 0)
        return active_capacity_;
    double capacity {0};
    for (auto &child : children_){
        capacity += child->getCapacity();
    }
    return capacity;
}

vector<double> Component::getCapacityLoss() {
    return capacity_loss_;
}


#pragma clang diagnostic pop