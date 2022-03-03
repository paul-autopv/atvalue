//
// Created by Paul on 2/28/22.
//

#include "ProductionReport.h"

void ProductionReport::logIncident(const Incident& incident) {
    incidents_.push_back(incident);

}

vector<Incident> ProductionReport::getIncidents() {
    return incidents_;
}

void ProductionReport::logProductionLoss(const int &component_id, vector<double> production_loss) {

    if (accumulate(production_loss.begin(), production_loss.end(), 0.) > 0)
        production_loss_.insert(pair<int, vector<double>>(component_id, production_loss));
}

ProductionLoss ProductionReport::getProductionLoss() {
    return production_loss_;
}
