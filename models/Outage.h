//
// Created by Paul.Nel on 22/02/2022.
//

#ifndef ATVALUE_OUTAGE_H
#define ATVALUE_OUTAGE_H


#include "OutageSchedule.h"
#include "OutageCost.h"
#include "OutageType.h"

class Outage {

public:
    Outage() = delete;
    Outage(int id, int unit_id, OutageType type, OutageSchedule schedule, OutageCost cost):
        id_ {id},
        unit_id_ {unit_id},
        type_ {type},
        schedule_ {schedule},
        cost_ {cost}{}

    int start() const{
        return schedule_.start();
    }

    int end() const{
        return schedule_.end();
    }

    int duration() const{
        return schedule_.duration();
    }

    double capex_cost() const{
        return cost_.capex();
    }

    double opex_cost() const{
        return cost_.opex();
    }

    double total_cost() const{
        return cost_.total();
    }

    double daily_cost() const{
        return total_cost() / duration();
    }

    OutageType type() const{
        return type_;
    }

private:
    int id_;
    int unit_id_;
    OutageType type_;
    OutageSchedule schedule_;
    OutageCost cost_;

};


#endif //ATVALUE_OUTAGE_H
