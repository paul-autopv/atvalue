//
// Created by Paul on 2022/01/01.
//

#include "FailureMode.h"

#include <utility>

FailureMode::FailureMode(const FailureModeDetail& detail, unique_ptr<IProbability> distribution):
    id_ {detail.id},
    unit_id_ {detail.unit_id},
    name_ {detail.name},
    description_ {detail.description},
    tag_ {detail.tag},
    distribution_ {move(distribution)}  {
}

int FailureMode::getId() const {
    return id_;
}

int FailureMode::getUnitId() const {
    return unit_id_;
}

double FailureMode::getFailureProbability(const int &day) const {
    return distribution_->getProbability(day);
}

string FailureMode::getDescription() const {
    return description_;
}

string FailureMode::getName() const {
    return name_;
}

string FailureMode::getTag() const {
    return tag_;
}
