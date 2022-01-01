//
// Created by Paul on 2022/01/01.
//

#include "FailureModes.h"

const std::string &FailureModes::getName() const {
    return name;
}

void FailureModes::setName(const std::string &name) {
    FailureModes::name = name;
}

const std::string &FailureModes::getDescription() const {
    return description;
}

void FailureModes::setDescription(const std::string &description) {
    FailureModes::description = description;
}

const std::string &FailureModes::getTag() const {
    return tag;
}

void FailureModes::setTag(const std::string &tag) {
    FailureModes::tag = tag;
}
