//
// Created by Paul on 2022/01/17.
//

#ifndef TREE_SIMULATOR_H
#define TREE_SIMULATOR_H

#include <memory>
#include <thread>
#include <mutex>

#include "../models/Facility.h"

class Simulator {
    int simulations_;
    std::unique_ptr<Facility> facility_;
    static void printProgress(int id);

public:
    Simulator() = delete;
    Simulator(int simulations, std::unique_ptr <Facility> facility);

    void run();

};


#endif //TREE_SIMULATOR_H
