//
// Created by Paul on 2022/01/01.
//

#include "FailureMode.h"

#include <utility>


FailureMode::FailureMode(string name, string description, string tag, std::unique_ptr<IProbability> probability) :
name_ {std::move(name)}, description_ {std::move(description)}, tag_ {std::move(tag)},
probability_ {move(probability)}{

}
