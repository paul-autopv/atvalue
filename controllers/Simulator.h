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

using Task_type = ProductionReport();

class Simulator {

public:
    Simulator() = delete;
    Simulator(const int &simulations, const int &duration, InputMap failures, InputMap structure);
    void run() const;
    void run_single() const;

private:

    int simulations_;
    int simulation_duration_;
    InputMap failures_;
    InputMap structure_;

    void prepareOutputFiles();
    void reportToCsv(ProductionReport report) const;

    static void reportIncidents(vector<Incident> &report);

    void reportProductionLoss(ProductionLoss &report) const;

    static void prepareOutputFile(const string& name, const string& header);

    ProductionLoss getComponentAverageProductionLoss(ProductionLoss &report) const;
};

static std::string incident_register_path_ {"../output/"};

#endif //ATVALUE_SIMULATOR_H
