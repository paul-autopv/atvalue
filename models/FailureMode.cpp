//
// Created by Paul on 2022/01/01.
//

#include "FailureMode.h"

const std::string &FailureMode::getName() const {
    return name;
}

void FailureMode::setName(const std::string &name) {
    FailureMode::name = name;
}

const std::string &FailureMode::getDescription() const {
    return description;
}

void FailureMode::setDescription(const std::string &description) {
    FailureMode::description = description;
}

const std::string &FailureMode::getTag() const {
    return tag;
}

void FailureMode::setTag(const std::string &tag) {
    FailureMode::tag = tag;
}
