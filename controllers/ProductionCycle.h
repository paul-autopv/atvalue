#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
#pragma ide diagnostic ignored "modernize-pass-by-value"
//
// Created by Paul on 2022/01/25.
//


#ifndef ATVALUE_PRODUCTIONCYCLE_H
#define ATVALUE_PRODUCTIONCYCLE_H

#include "../models/Facility.h"

#include <random>

class  ProductionCycle{
public:
    ProductionCycle();

    ProductionCycle(const int &duration, const InputMap &structure,const InputMap &failures);

    int operator()();

private:
    int duration_;
    InputMap structure_;
    InputMap failures_;
    shared_ptr<Facility> facility_;

    bool hasOccurredFailure(int day, const int &risk, double probability);
};


#endif //ATVALUE_PRODUCTIONCYCLE_H


#pragma clang diagnostic pop