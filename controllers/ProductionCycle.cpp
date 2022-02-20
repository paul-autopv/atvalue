//
// Created by Paul on 2/20/22.
//

#include "ProductionCycle.h"

ProductionCycle::ProductionCycle() : ProductionCycle(0, InputMap(), InputMap()) {}

ProductionCycle::ProductionCycle(const int &duration, const InputMap &structure,const InputMap &failures) :
        duration_ {duration}, structure_ {structure}, failures_ {failures}{
    register_.resize(duration_);
};
§

vector<int> ProductionCycle::operator()() {
    vector<int> temp(duration_);
    for (int i = 0; i < duration_; ++i) {
        temp[i] = 1;
    }
    for (int i = 0; i < duration_; ++i) {
        register_[i] += temp[i];
    }
    return register_;
}