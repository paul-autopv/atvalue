#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
#pragma ide diagnostic ignored "modernize-pass-by-value"
//
// Created by Paul on 2022/01/25.
//


#ifndef ATVALUE_PRODUCTIONCYCLE_H
#define ATVALUE_PRODUCTIONCYCLE_H

#include "../controllers/Simulator.h"
#include "../models/OutageManager.h"

#include <random>



class  ProductionCycle{
public:
    ProductionCycle();

    ProductionCycle(const int &duration, const InputMap &structure,const InputMap &failures);

    IncidentRegister operator()();

private:
    int duration_;
    InputMap structure_;
    InputMap failures_;
    shared_ptr<Facility> facility_;
    OutageManager outageManager_ = OutageManager();
    IncidentRegister incidentRegister_;

    bool hasOccurredFailure(const int &day, const int &failureId, const double &probability);
    void resolveFailure(const FailureModeDetail &failureModeDetail, const int &day);
    void recordFailure(const int &incident, const int &day, FailureModeDetail &event);
    int scheduleOutageType(const FailureModeDetail &failureModeDetail, int start, int duration,
                           OutageType type, OutageCost cost);
};


#endif //ATVALUE_PRODUCTIONCYCLE_H


#pragma clang diagnostic pop