//
// Created by Paul on 2022/01/01.
//

#include "FailureMode.h"

#include <utility>


FailureMode::FailureMode(int id, int unit_id, string name, string description, string tag,
                         std::unique_ptr<IProbability> distribution) :
        id_ {id},
        unit_id_ {unit_id},
        name_ {std::move(name)},
        description_ {std::move(description)},
        tag_ {std::move(tag)},
        distribution_ {move(distribution)}{

}

FailureMode::FailureMode(const FailureMode &other) {
    id_ = other.id_;
    unit_id_ = other.unit_id_;
    name_ = other.name_;
    description_ = other.description_;
    tag_ = other.tag_;
    distribution_ = std::unique_ptr<IProbability>();
    auto dist = *other.distribution_;
    *distribution_ = *other.distribution_;
}

FailureMode &FailureMode::operator=(const FailureMode &other) {
    if (this == &other)
        return *this;
    id_ = other.id_;
    unit_id_ = other.unit_id_;
    name_ = other.name_;
    description_ = other.description_;
    tag_ = other.tag_;
    distribution_ = std::unique_ptr<IProbability>();
    *distribution_ = *other.distribution_;
    return *this;
}

int FailureMode::getId() const {
    return id_;
}

int FailureMode::getUnitId() const {
    return unit_id_;
}

bool FailureMode::hasOccurred(const double &probability, const int &day) const {
    return probability < distribution_->getProbability(day);
}

