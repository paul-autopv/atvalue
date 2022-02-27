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
        auto failuresForDay = facility_->getShuffledFailureModeIds();
        for (auto &failureId : failuresForDay){
            auto probability = likelihood();
            if (hasOccurredFailure(day, failureId, probability)){
                cout << "Day: " << day << " Failure :" << failureId << " Probability " << probability <<endl;
                auto failure_detail = facility_->getFailureModeDetail(failureId);
                shutDownAffectedComponents(failure_detail.component_id, failure_detail.scope);
                recordFailure(incident, day, failure_detail);
                resolveFailure(failure_detail, day);
                ++incident;
            }
        }
    }
    return incidentRegister_;
}

bool ProductionManager::hasOccurredFailure(const int &day, const int &failureId, const double &probability) {
    if (isComponentOnline(failureId)){
        auto cumulativeProbability = facility_->getFailureModeProbability(failureId, day);
        return cumulativeProbability  > probability;
    }
    return false;
}

bool ProductionManager::isComponentOnline(const int &failure_id) {
    auto failure = facility_->getFailureModeDetail(failure_id);
    auto component = facility_->getComponentPtr(failure.component_id);
    if (component) {
        auto is_online = component->isOnline();
        return component->isOnline();
    }
    return false;
}

void ProductionManager::recordFailure(const int &incident, const int &day, FailureModeDetail &event) {
    auto simulation = to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));
    auto event_record = event.toString();
    event_record.push_back(to_string(day));
    event_record.push_back(simulation);
    incidentRegister_.insert(pair<int, vector<string>>(incident, event_record));
}

void ProductionManager::resolveFailure(const FailureModeDetail &failureModeDetail, const int &day) {

    scheduleOutage(failureModeDetail, day);
    repairComponent(failureModeDetail, day);
}

void ProductionManager::scheduleOutage(const FailureModeDetail &detail, const int &day) {
    int start = day;
    auto cost = OutageCost(0,0);
    start = scheduleOutageOfType(detail, start, detail.days_to_investigate, OutageType::investigation, cost);
    start = scheduleOutageOfType(detail, start, detail.days_to_procure, OutageType::procurement, cost);
    cost = OutageCost(detail.capex, detail.opex);
    scheduleOutageOfType(detail, start, detail.days_to_repair, OutageType::repair, cost) ;
}

void ProductionManager::repairComponent(const FailureModeDetail &detail, const int &day) {
    auto component_id = detail.component_id;
    auto failure_id = detail.id;
    auto component = facility_->getComponentPtr(component_id);
    auto previous_installed = component->getDaysInstalled();
    auto failure_mode = failures_.at(failure_id);
    component->setDaysInstalled(day);
    facility_->resetFailureModeProbability(day, failure_id);
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

void ProductionManager::shutDownAffectedComponents(const int &component_id, FailureScope scope) {
    if (scope == FailureScope::all){
        auto component = facility_->getRootComponentPtr();
        component->shutdown();
    }
    if (scope == FailureScope::parent){
        auto child = facility_->getComponentPtr(component_id);
        auto parent = facility_->getComponentPtr(child->getParentId());
        parent->shutdown();
    }
    if (scope == FailureScope::cascade){
        auto component = facility_->getComponentPtr(component_id);
        component->shutdown();
    }
}

#pragma clang diagnostic pop