//
// Created by Paul on 2022/01/17.
//

#ifndef ATVALUE_TRIANGULARPROBABILITY_H
#define ATVALUE_TRIANGULARPROBABILITY_H


#include "../models/IProbability.h"

class TriangularProbability : public IProbability{
    int installed_ {0};
    int should_fail_ {0};
    int will_fail_ {0};
public:
    TriangularProbability() = delete;
    TriangularProbability(const int &installed, const int &should_fail, const int &will_fail){
        if (will_fail < should_fail || installed > should_fail)
            throw std::invalid_argument("Ensure that will_fail >= should_fail >= installed.");
        installed_ = installed;
        should_fail_ = should_fail;
        will_fail_ = will_fail;
    };

    double getProbability(const int &day) override{
        if (day < installed_)
            return 0;
        if (day >= will_fail_)
            return 1;
        auto weight = will_fail_ - installed_; // set height of 'triangle' to same as base to prevent small fractions
        auto denominator = (weight * (will_fail_ - installed_)) / 2;
        auto pre_should_fail = (weight * (should_fail_ - installed_)) / 2;
        auto post_should_fail = (weight * (will_fail_ - should_fail_)) / 2;
        if (day <= should_fail_){
            return (((day - (double)installed_)/((double)should_fail_ - (double)installed_)) * pre_should_fail) / denominator;
        }
        return ((pre_should_fail + ((day - (double)should_fail_) / ((double)will_fail_ - (double)should_fail_)) * post_should_fail )) / denominator;
    };
};


#endif //ATVALUE_TRIANGULARPROBABILITY_H
