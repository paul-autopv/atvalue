//
// Created by Paul on 2022/01/01.
//

#ifndef TREE_WEIBULLPROBABILITY_H
#define TREE_WEIBULLPROBABILITY_H

#include "../models/IProbability.h"

class WeibullProbability : IProbability {
    double alpha;
    double beta;
public:
    WeibullProbability() = delete;
    WeibullProbability(double alpha, double beta);

    bool hasOccurred() override;
};


#endif //TREE_WEIBULLPROBABILITY_H
