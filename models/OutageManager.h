//
// Created by Paul on 2/22/22.
//

#ifndef ATVALUE_OUTAGEMANAGER_H
#define ATVALUE_OUTAGEMANAGER_H


#include <vector>
#include "Outage.h"

class OutageManager {



public:
    void scheduleOutage(OutageSchedule schedule, OutageType type, OutageCost cost, int unit_id);

private:
    static int outage_count_;
    std::vector<Outage> outages_;
};


#endif //ATVALUE_OUTAGEMANAGER_H
