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

void ProductionReport::logProductionLoss(const int &component_id, vector<double> production_loss, bool all=false) {

    if (!all) {
        if (accumulate(production_loss.begin(), production_loss.end(), 0.) > 0)
            production_loss_.insert(pair<int, vector<double>>(component_id, production_loss));
    }
    production_loss_.insert(pair<int, vector<double>>(component_id, production_loss));
}

void ProductionReport::logAvailability(const int &component_id, const vector<bool>& availability) {

    availability_.insert(pair<int, vector<bool>>(component_id, availability));
}

ProductionRegister ProductionReport::getProductionLoss() {
    return production_loss_;
}

ProductionRegister ProductionReport::getAvailability() {
    map<int, vector<double>> avail;
    for (auto &item : availability_){
        vector<double> daily_availability;
        for (auto && i : item.second){
             daily_availability.push_back((double) i);
        }
        avail.insert(pair(item.first, daily_availability));
    }
    return avail;
}
