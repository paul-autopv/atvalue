//
// Created by Paul on 2/22/22.
//

#include "OutageManager.h"

int OutageManager::outage_count_ = 0;

void OutageManager::scheduleOutage(int component_id, OutageType type, OutageSchedule schedule, OutageCost cost) {
    auto outage_id = nextId();
    outages_.emplace_back(outage_id, component_id, type, schedule, cost);
//    set component availability
}

Outagelist OutageManager::getAllOutages() {
    return outages_;
}

int OutageManager::nextId() {
    return ++outage_count_;
}
