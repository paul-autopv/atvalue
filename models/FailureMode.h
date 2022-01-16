//
// Created by Paul on 2022/01/01.
//

#ifndef TREE_FAILUREMODE_H
#define TREE_FAILUREMODE_H


#include <string>
#include "IProbability.h"

using namespace std;

class FailureMode {
    string name;
    string description;
    string tag;
    unique_ptr<IProbability> probability;

public:

    FailureMode() = delete;
    explicit FailureMode(unique_ptr<IProbability> probability);

};


#endif //TREE_FAILUREMODE_H
