//
// Created by Paul on 2022/01/01.
//

#include "FailureMode.h"

#include <utility>


FailureMode::FailureMode(unsigned id, unsigned unit_id, string name, string description, string tag,
                         std::unique_ptr<IProbability> probability) :
id_ {id}, unit_id_ {unit_id}, name_ {std::move(name)}, description_ {std::move(description)},
tag_ {std::move(tag)}, probability_ {move(probability)}{

}

unsigned FailureMode::getId() const {
    return id_;
}

unsigned FailureMode::getUnitId() const {
    return unit_id_;
}
