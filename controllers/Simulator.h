//
// Created by Paul on 2022/01/17.
//

#ifndef TREE_SIMULATOR_H
#define TREE_SIMULATOR_H

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

    static TypeRegister& sumRegister(TypeRegister& a, TypeRegister& b);

public:
    Simulator() = delete;
    Simulator(const int &simulations, const int &duration, std::unique_ptr<Facility> facility);

    void run() const;

    void run_single() const;
};


#endif //TREE_SIMULATOR_H
