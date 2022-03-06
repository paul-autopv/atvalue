//
// Created by Paul on 2/28/22.
//

#ifndef ATVALUE_PRODUCTIONREPORT_H
#define ATVALUE_PRODUCTIONREPORT_H

#include "../models/Facility.h"

using ProductionRegister = map<int, vector<double>>;
using Availability = map<int, vector<bool>>;

class ProductionReport{

public:
    void logIncident(const Incident& incident);
    void logProductionLoss(const int &component_id, vector<double> production_loss, bool all);
    void logAvailability(const int &component_id, const vector<bool>& availability);

    vector<Incident> getIncidents();
    ProductionRegister getProductionLoss();
    ProductionRegister getAvailability();

private:
    vector<Incident> incidents_;
    ProductionRegister production_loss_;
    Availability availability_;

};

#endif //ATVALUE_PRODUCTIONREPORT_H
