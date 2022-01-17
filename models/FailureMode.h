//
// Created by Paul on 2022/01/01.
//

#ifndef TREE_FAILUREMODE_H
#define TREE_FAILUREMODE_H


#include <string>
#include "IProbability.h"

using namespace std;

class FailureMode {
    unsigned id_;
    string name_;
    string description_;
    string tag_;
    unique_ptr<IProbability> probability_;

public:

    FailureMode() = delete;
    FailureMode(unsigned id, string name, string description, string tag, std::unique_ptr<IProbability> probability);

    unsigned getId() const;

};


#endif //TREE_FAILUREMODE_H
