//
// Created by Paul on 2/28/22.
//

#ifndef ATVALUE_PRODUCTIONREPORT_H
#define ATVALUE_PRODUCTIONREPORT_H

#include "../models/Facility.h"

class ProductionReport{

public:
    void logIncident(const Incident& incident);
    vector<Incident> getIncidents();

private:
    vector<Incident> incidents_;
};

#endif //ATVALUE_PRODUCTIONREPORT_H
