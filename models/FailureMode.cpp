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

double FailureMode::getCapex() const {
    return failureModeDetail_.capex;
}

double FailureMode::getOpex() const {
    return failureModeDetail_.opex;
}

int FailureMode::getDaysToInvestigate() const {
    return failureModeDetail_.days_to_investigate;
}
int FailureMode::getDaysToProcure() const {
    return failureModeDetail_.days_to_procure;
}
int FailureMode::getDaysToRepair() const {
    return failureModeDetail_.days_to_repair;
}

FailureModeDetail FailureMode::getFailureModeDetail() {
    return failureModeDetail_;
}

double FailureMode::getFailureProbability(const int &day) const {
    return distribution_->getProbability(day);
}
