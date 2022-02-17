//
// Created by Paul on 2022/01/01.
//

#ifndef TREE_WEIBULLPROBABILITY_H
#define TREE_WEIBULLPROBABILITY_H

#include <cmath>

#include "../models/IProbability.h"

class WeibullProbability : public IProbability {
    double alpha_ {0};
    double beta_ {0};
public:
    WeibullProbability() = delete;
    WeibullProbability(const double &alpha, const double &beta) : alpha_ {alpha}, beta_ {beta}{};

    double getProbability(const int &day) override {
        if (day < 0)
            return 0;
        auto exponent = -std::pow(day/beta_, alpha_);
        return 1 - std::exp(exponent);
    };
};

#endif //TREE_WEIBULLPROBABILITY_H
