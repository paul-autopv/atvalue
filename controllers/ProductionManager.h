#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
#pragma ide diagnostic ignored "modernize-pass-by-value"
//
// Created by Paul on 2022/01/25.
//


#ifndef ATVALUE_PRODUCTIONMANAGER_H
#define ATVALUE_PRODUCTIONMANAGER_H

#include "ProductionReport.h"
#include "../controllers/Simulator.h"
#include "../models/OutageManager.h"
#include "../models/enums/FailureScope.h"

#include <random>



class  ProductionManager{
public:
    ProductionManager();

    ProductionManager(const int &simulation_duration, const InputMap &structure, const InputMap &failures);

    ProductionReport operator()();

    bool hasOccurredFailure(const int &day, const int &failureId, const double &probability);
    bool isComponentOnline(const int &failure_id, const int &day);

private:
    int simulation_duration_;
    InputMap structure_;
    InputMap failures_;
    shared_ptr<Facility> facility_;
    OutageManager outageManager_ = OutageManager();
    ProductionReport report_;

    void shutDownAffectedComponents(const int &component_id, FailureScope scope, const int &day,
                                    const int &duration);
    void resolveFailure(const FailureModeDetail &failureModeDetail, const int &day);
    void recordFailure(const int &incident_id, const int &day, FailureModeDetail &event);
    void scheduleOutage(const FailureModeDetail &detail, const int &day);
    int scheduleOutageOfType(const FailureModeDetail &failureModeDetail, int start, int duration,
                             OutageType type, OutageCost cost);
    void repairComponent(const FailureModeDetail &detail, const int &day);

    void shutDown(const shared_ptr<Component>& component, const int &day, const int &duration) const;
};


#endif //ATVALUE_PRODUCTIONMANAGER_H


#pragma clang diagnostic pop