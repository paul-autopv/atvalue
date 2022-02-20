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

int FailureMode::getId() const {
    return id_;
}

int FailureMode::getUnitId() const {
    return unit_id_;
}

double FailureMode::getFailureProbability(const int &day) const {
    return distribution_->getProbability(day);
}
