#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-pass-by-value"
//
// Created by Paul on 2/20/22.
//

#include "ProductionCycle.h"

ProductionCycle::ProductionCycle() : ProductionCycle(0, InputMap(), InputMap()) {}

ProductionCycle::ProductionCycle(const int &duration, const InputMap &structure,const InputMap &failures) :
        duration_ {duration}, structure_ {structure}, failures_ {failures}{
    facility_ = make_shared<Facility>();
    facility_->buildFacility(structure_, failures_);
};


IncidentRegister ProductionCycle::operator()() {
    const int max {1'000'000};
    default_random_engine engine {};
    uniform_int_distribution distribution {0, max};
    auto likelihood = [&distribution, &engine](){ return (double)distribution(engine)/max; };

    auto incident {1};
    for (int day = 0; day < duration_; ++day) {
        auto failuresForToday = facility_->getShuffledFailureModes();
        for (auto &failureId : failuresForToday){
            auto probability = likelihood();
            if (hasOccurredFailure(day, failureId, probability)){
                auto failure_detail = facility_->getFailureModeDetail(failureId);
                recordFailure(incident, day, failure_detail);
                resolveFailure(failure_detail);
                ++incident;
            }
        }
    }
    return incidentRegister_;
}

bool ProductionCycle::hasOccurredFailure(const int &day, const int &failureId, const double &probability) {
    auto cumulativeProbability = facility_->getFailureModeProbability(failureId, day);
    return cumulativeProbability  > probability;
}

void ProductionCycle::recordFailure(int incident, int day, FailureModeDetail &event) {
    auto event_record = event.toString();
    event_record.push_back(to_string(day));
    incidentRegister_.insert(pair<int, vector<string>>(incident, event_record));
}

void ProductionCycle::resolveFailure(const FailureModeDetail& failureModeDetail) {
//    schedule outage
//    repair components
}



#pragma clang diagnostic pop