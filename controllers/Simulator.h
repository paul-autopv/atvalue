//
// Created by Paul on 2022/01/17.
//

#ifndef ATVALUE_SIMULATOR_H
#define ATVALUE_SIMULATOR_H

#include "../models/Facility.h"
#include "../controllers/ProductionManager.h"

#include <memory>
#include <thread>
#include <mutex>
#include <future>
#include <deque>
#include <utility>
#include <fstream>

using Task_type = IncidentRegister();
using Register = IncidentRegister;

class Simulator {

public:
    Simulator() = delete;
    Simulator(const int &simulations, const int &duration, InputMap failures, InputMap structure);
    void run() const;
    void run_single() const;

private:
    int simulations_;
    const int simulation_duration_;
    InputMap failures_;
    InputMap structure_;
    static constexpr auto incident_register_path_ = "../output/incidents.csv";

    static void prepareOutputFiles();
    static void writeRegisterToCsv(const Register& the_register) ;
};


#endif //ATVALUE_SIMULATOR_H
