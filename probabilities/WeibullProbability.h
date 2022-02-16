//
// Created by Paul on 2022/01/01.
//

#ifndef TREE_WEIBULLPROBABILITY_H
#define TREE_WEIBULLPROBABILITY_H

#include <cmath>

#include "../models/IProbability.h"

class WeibullProbability : public IProbability {
    double alpha_;
    double beta_;
public:
    WeibullProbability() = delete;
    WeibullProbability(double alpha, double beta) : alpha_ {alpha}, beta_ {beta}{};

    double getProbability(int day) override;
};

double WeibullProbability::getProbability(int day) {
    if (day < 0)
        return 0;
    auto exponent = -std::pow(day/beta_, alpha_);
    return 1 - std::exp(exponent);
}

#endif //TREE_WEIBULLPROBABILITY_H
