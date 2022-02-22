//
// Created by Paul on 2/22/22.
//

#ifndef ATVALUE_OUTAGEMANAGER_H
#define ATVALUE_OUTAGEMANAGER_H


#include <vector>
#include "Outage.h"

using Outagelist = std::vector<Outage>;

class OutageManager {

public:
    static int outage_count_;
    void scheduleOutage(OutageSchedule schedule, OutageType type, OutageCost cost, int unit_id);
    Outagelist getAllOutages();

private:
    Outagelist outages_;

    static int nextId();
};


#endif //ATVALUE_OUTAGEMANAGER_H
