//
// Created by Paul on 2022/01/17.
//

#ifndef TREE_TRIANGULARPROBABILITY_H
#define TREE_TRIANGULARPROBABILITY_H


#include "../models/IProbability.h"

class TriangularProbability : public IProbability{
    unsigned days_to_should_fail;
    unsigned days_to_will_fail;
public:
    TriangularProbability() = delete;
    TriangularProbability(unsigned should_fail, unsigned will_fail);

    double getProbability(int day) override;
};


#endif //TREE_TRIANGULARPROBABILITY_H
