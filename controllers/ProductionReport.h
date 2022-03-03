//
// Created by Paul on 2/28/22.
//

#ifndef ATVALUE_PRODUCTIONREPORT_H
#define ATVALUE_PRODUCTIONREPORT_H

#include "../models/Facility.h"

using ProductionLoss = map<int, vector<double>>;

class ProductionReport{

public:
    void logIncident(const Incident& incident);
    void logProductionLoss(const int &component_id, vector<double> production_loss);

    vector<Incident> getIncidents();
    ProductionLoss getProductionLoss();

private:
    vector<Incident> incidents_;
    ProductionLoss production_loss_;
};

#endif //ATVALUE_PRODUCTIONREPORT_H
