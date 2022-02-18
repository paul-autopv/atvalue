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
    std::unique_ptr<Facility> facility_;
    inline static mutex cout_mutex;

    static TypeRegister& sumRegister(TypeRegister& a, TypeRegister& b);

public:
    Simulator() = delete;
    Simulator(int simulations, std::unique_ptr<Facility> facility, int duration);

    void run() const;

    void run_single() const;
};


#endif //ATVALUE_SIMULATOR_H
