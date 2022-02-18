//
// Created by Paul on 2022/01/17.
//

#ifndef ATVALUE_SIMULATOR_H
#define ATVALUE_SIMULATOR_H

#include <memory>
#include <thread>
#include <mutex>
#include <future>
#include <deque>

#include "../models/Facility.h"

class Simulator {

    using TypeRegister = vector<int>;

    int simulations_;
    const int duration_;
    InputMap failures_;
    InputMap structure_;


    static TypeRegister& sumRegister(TypeRegister& a, TypeRegister& b);

public:
    Simulator() = delete;
    Simulator(const int &simulations, const int &duration, InputMap failures, InputMap structure);


    void run() const;

    void run_single() const;
};


#endif //ATVALUE_SIMULATOR_H
