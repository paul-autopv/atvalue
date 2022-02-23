//
// Created by Paul on 2022/01/01.
//

#include "FailureMode.h"

#include <utility>

FailureMode::FailureMode(FailureModeDetail  detail, unique_ptr<IProbability> distribution):
    failureModeDetail_ {std::move(detail)},
    distribution_ {move(distribution)}  {
}

int FailureMode::getId() const {
    return failureModeDetail_.id;
}

int FailureMode::getUnitId() const {
    return failureModeDetail_.unit_id;
}

double FailureMode::getFailureProbability(const int &day) const {
    return distribution_->getProbability(day);
}

string FailureMode::getDescription() const {
    return failureModeDetail_.description;
}

string FailureMode::getName() const {
    return failureModeDetail_.name;
}

string FailureMode::getTag() const {
    return failureModeDetail_.tag;
}

FailureModeDetail FailureMode::getFailureModeDetail() {
    return failureModeDetail_;
}
