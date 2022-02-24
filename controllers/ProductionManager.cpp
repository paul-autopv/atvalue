#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-pass-by-value"
//
// Created by Paul on 2/20/22.
//

#include "ProductionManager.h"

ProductionManager::ProductionManager() : ProductionManager(0, InputMap(), InputMap()) {}

ProductionManager::ProductionManager(const int &duration, const InputMap &structure, const InputMap &failures) :
        duration_ {duration}, structure_ {structure}, failures_ {failures}{
    facility_ = make_shared<Facility>();
    facility_->buildFacility(structure_, failures_);
};


IncidentRegister ProductionManager::operator()() {
    const int max {1'000'000};
    default_random_engine engine {};
    uniform_int_distribution distribution {0, max};
    auto likelihood = [&distribution, &engine](){ return (double)distribution(engine)/max; };

    auto incident {1};
    for (int day = 0; day < duration_; ++day) {
        auto failuresForDay = facility_->getShuffledFailureModes();
        for (auto &failureId : failuresForDay){
            auto probability = likelihood();
            if (hasOccurredFailure(day, failureId, probability)){
                auto failure_detail = facility_->getFailureModeDetail(failureId);
                recordFailure(incident, day, failure_detail);
                resolveFailure(failure_detail, day);
                ++incident;
            }
        }
    }
    return incidentRegister_;
}

bool ProductionManager::hasOccurredFailure(const int &day, const int &failureId, const double &probability) {
//    Verify component is available
    auto cumulativeProbability = facility_->getFailureModeProbability(failureId, day);
    return cumulativeProbability  > probability;
}

void ProductionManager::recordFailure(const int &incident, const int &day, FailureModeDetail &event) {
    auto event_record = event.toString();
    event_record.push_back(to_string(day));
    incidentRegister_.insert(pair<int, vector<string>>(incident, event_record));
}

void ProductionManager::resolveFailure(const FailureModeDetail &failureModeDetail, const int &day) {

    scheduleOutage(failureModeDetail, day);
    repairComponent();
}

void ProductionManager::scheduleOutage(const FailureModeDetail &detail, const int &day) {
    int start = day;
    auto cost = OutageCost(0,0);
    start = scheduleOutageOfType(detail, start, detail.days_to_investigate, OutageType::investigation, cost);
    start = scheduleOutageOfType(detail, start, detail.days_to_procure, OutageType::procurement, cost);
    cost = OutageCost(detail.capex, detail.opex);
    scheduleOutageOfType(detail, start, detail.days_to_repair, OutageType::repair, cost) ;
}

void ProductionManager::repairComponent() {

}


int ProductionManager::scheduleOutageOfType(const FailureModeDetail &failureModeDetail, int start, int duration,
                                            OutageType type, OutageCost cost) {
    if (duration | cost.isNotZero()){
        auto schedule = OutageSchedule(start, duration);
        outageManager_.scheduleOutage(failureModeDetail.component_id, type, schedule, cost);
        start += duration;
    }
    return start;
}


#pragma clang diagnostic pop