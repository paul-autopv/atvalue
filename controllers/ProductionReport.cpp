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
