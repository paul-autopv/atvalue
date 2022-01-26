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
    int simulations_;
    const int duration_;
    std::unique_ptr<Facility> facility_;
    inline static mutex cout_mutex;

public:
    Simulator() = delete;
    Simulator(int simulations, std::unique_ptr<Facility> facility, int duration);

    void run();

    void run_single();
};


#endif //TREE_SIMULATOR_H
