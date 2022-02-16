//
// Created by Paul on 2022/01/17.
//

#ifndef TREE_TRIANGULARPROBABILITY_H
#define TREE_TRIANGULARPROBABILITY_H


#include "../models/IProbability.h"

class TriangularProbability : public IProbability{
    double installed_;
    double should_fail_;
    double will_fail_;
public:
    TriangularProbability() = delete;
    TriangularProbability(int installed, int should_fail, int will_fail){
        if (will_fail < should_fail || installed > should_fail)
            throw std::invalid_argument("Ensure that will_fail >= should_fail >= installed.");
        installed_ = (double) installed;
        should_fail_ = (double) should_fail;
        will_fail_ = (double) will_fail;
    };

    double getProbability(int day) override{
        if (day < installed_)
            return 0;
        if (day >= will_fail_)
            return 1;
        auto weight = will_fail_ - installed_; // set height of triangle to same length as base to prevent small fractions
        auto denominator = (weight * (will_fail_ - installed_)) / 2;
        auto pre_should_fail = (weight * (should_fail_ - installed_)) / 2;
        auto post_should_fail = (weight * (will_fail_ - should_fail_)) / 2;
        if (day <= should_fail_){
            return (((day - installed_)/(should_fail_ - installed_)) * pre_should_fail) / denominator;
        }
        return ((pre_should_fail + ((day - should_fail_) / (will_fail_ - should_fail_)) * post_should_fail )) / denominator;
    };
};


#endif //TREE_TRIANGULARPROBABILITY_H
