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
    Outage(int id, int component_id, OutageType type, OutageSchedule schedule, OutageCost cost):
            id_ {id},
            component_id {component_id},
            type_ {type},
            schedule_ {schedule},
            cost_ {cost}{}

    int start() const;
    int end() const;
    int duration() const;
    int id() const;
    double capex_cost() const;
    double opex_cost() const;
    double total_cost() const;
    double daily_cost() const;
    OutageType type() const;

private:
    int id_;
    int component_id;
    OutageType type_;
    OutageSchedule schedule_;
    OutageCost cost_;
};


#endif //ATVALUE_OUTAGE_H
