//
// Created by Paul.Nel on 22/02/2022.
//

#include "Outage.h"

int Outage::start() const{
    return schedule_.start();
}

int Outage::end() const{
    return schedule_.end();
}

int Outage::duration() const{
    return schedule_.duration();
}

double Outage::capex_cost() const{
    return cost_.capex();
}

double Outage::opex_cost() const{
    return cost_.opex();
}

double Outage::total_cost() const{
    return cost_.total();
}

double Outage::daily_cost() const{
    auto outage_duration = duration();
    if (outage_duration <= 0)
        return 0;
    return total_cost() / outage_duration;
}

OutageType Outage::type() const{
    return type_;
}

int Outage::id() const {
    return id_;
}
