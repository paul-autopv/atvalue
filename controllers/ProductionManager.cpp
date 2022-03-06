#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-pass-by-value"
//
// Created by Paul on 2/20/22.
//

#include "ProductionManager.h"

ProductionManager::ProductionManager() : ProductionManager(0, InputMap(), InputMap()) {}

ProductionManager::ProductionManager(const int &simulation_duration, const InputMap &structure, const InputMap &failures) :
        simulation_duration_ {simulation_duration}, structure_ {structure}, failures_ {failures}{
    facility_ = make_shared<Facility>(simulation_duration_);
    facility_->buildFacility(structure_, failures_);
};


ProductionReport ProductionManager::operator()() {
    const int max {1'000'000};
    typedef std::chrono::high_resolution_clock my_clock;
    my_clock::time_point beginning = my_clock::now();
    my_clock::duration d = my_clock::now() - beginning;
    default_random_engine engine {};
    engine.seed(d.count());

    uniform_int_distribution distribution {0, max};
    auto likelihood = [&distribution, &engine](){ return (double)distribution(engine)/max; };

    auto incident {1};
    for (int day = 0; day < simulation_duration_; ++day) {
        auto failuresForDay = facility_->getShuffledFailureModeIds();
        for (auto &failureId : failuresForDay){
            auto probability = likelihood();
            if (hasOccurredFailure(day, failureId, probability)){
                auto failure_detail = facility_->getFailureModeDetail(failureId);
                cout << "Day: " << day << " Component: " << failure_detail.component_id << " Failure: " << failureId << " Probability: " << probability <<endl;
                auto outage_duration = failure_detail.days_to_investigate + failure_detail.days_to_procure + failure_detail.days_to_repair;
                shutDownAffectedComponents(failure_detail.component_id, failure_detail.scope, day, outage_duration);
                recordFailure(incident, day, failure_detail);
                resolveFailure(failure_detail, day);
                ++incident;
            }
        }
    }
    logComponentFailures();
    return report_;
}

void ProductionManager::logComponentFailures() {
    for (auto &component : facility_->getComponents()){
        report_.logProductionLoss(component.first, component.second->getCapacityLoss(), true);
        report_.logAvailability(component.first, component.second->getAvailability());
    }
}

bool ProductionManager::hasOccurredFailure(const int &day, const int &failureId, const double &probability) {
    if (isComponentOnline(failureId, day)){
        auto cumulativeProbability = facility_->getFailureModeProbability(failureId, day);
        return cumulativeProbability  > probability;
    }
    return false;
}

void ProductionManager::shutDownAffectedComponents(const int &component_id, FailureScope scope, const int &day,
                                                   const int &duration) {
    if (scope == FailureScope::all){
        shutDown(facility_->getRootComponentPtr(), day, duration);
    }
    else if (scope == FailureScope::parent){
        auto component = facility_->getComponentPtr(component_id);
        shutDown(facility_->getComponentPtr(component->getParentId()), day, duration);
    }
    else if (scope == FailureScope::component){
        shutDown(facility_->getComponentPtr(component_id), day, duration);
    }
    else
        throw invalid_argument("Undefined FailureScope" + (string) reinterpret_cast<const char *>(static_cast<unsigned char>(scope)));
}

void ProductionManager::shutDown(const shared_ptr<Component>& component, const int &day, const int &duration) const {
    component->scheduleOutage( day, duration);
    component->scheduleCapacityLoss(day, duration);
}

void ProductionManager::recordFailure(const int &incident_id, const int &day, FailureModeDetail &event) {
    auto simulation = to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));
    auto event_record = event.toString();
    event_record.push_back(to_string(day));
    event_record.push_back(simulation);
    report_.logIncident(Incident(incident_id, event_record));
}

void ProductionManager::resolveFailure(const FailureModeDetail &failureModeDetail, const int &day) {

    scheduleOutage(failureModeDetail, day);
    repairComponent(failureModeDetail, day);
}

bool ProductionManager::isComponentOnline(const int &failure_id, const int &day) {
    auto failure = facility_->getFailureModeDetail(failure_id);
    auto component = facility_->getComponentPtr(failure.component_id);
    if (component) {
        return component->isOnline(day);
    }
    return false;
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
    auto component = facility_->getComponentPtr(detail.component_id);
    auto failure_mode = failures_.at(detail.id);
    component->setDayInstalled(day);
    facility_->resetFailureModeProbability(day, detail.id);
}

int ProductionManager::scheduleOutageOfType(const FailureModeDetail &failureModeDetail, int start, int duration,
                                            OutageType type, OutageCost cost) {
    if (duration | cost.isNotZero()){
        auto schedule = OutageSchedule(start, duration);
        outageManager_.recordOutage(failureModeDetail.component_id, type, schedule, cost);
        start += duration;
    }
    return start;
}

#pragma clang diagnostic pop