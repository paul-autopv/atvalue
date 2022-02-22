//
// Created by Paul on 2/22/22.
//

#include "OutageManager.h"

void OutageManager::scheduleOutage(OutageSchedule schedule, OutageType type, OutageCost cost, int unit_id) {
    auto outage_id = ++OutageManager::outage_count_;
    outages_.emplace_back(outage_id, unit_id, type, schedule, cost);
}
