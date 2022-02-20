#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
#pragma ide diagnostic ignored "modernize-pass-by-value"
//
// Created by Paul on 2022/01/25.
//


#ifndef ATVALUE_PRODUCTIONCYCLE_H
#define ATVALUE_PRODUCTIONCYCLE_H


class  ProductionCycle{
public:
    ProductionCycle() : ProductionCycle(0, InputMap(), InputMap()) {};

    ProductionCycle(const int &duration, const InputMap &structure,const InputMap &failures) :
    duration_ {duration}, structure_ {structure}, failures_ {failures}{
        register_.resize(duration_);
    };

    vector<int> operator()() {
        vector<int> temp(duration_);
        for (int i = 0; i < duration_; ++i) {
                temp[i] = 1;
        }
        for (int i = 0; i < duration_; ++i) {
            register_[i] += temp[i];
        }
        return register_;
    }

private:
    int duration_;
    InputMap structure_;
    InputMap failures_;
    vector<int> register_;
};


#endif //ATVALUE_PRODUCTIONCYCLE_H


#pragma clang diagnostic pop