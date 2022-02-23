//
// Created by Paul on 2/22/22.
//

#ifndef ATVALUE_FAILUREMODEDETAIL_H
#define ATVALUE_FAILUREMODEDETAIL_H

#include <string>
#include <utility>
#include <vector>

class FailureModeDetail{

public:
    FailureModeDetail() = default;
    FailureModeDetail(int id, int unit_id, std::string name, std::string description, std::string tag, double capex,
                      double opex, int days_to_investigate, int days_to_procure, int days_to_repair) :
            id {id},
            component_id {unit_id},
            name {std::move(name)},
            description {std::move(description)},
            tag {std::move(tag)},
            capex {capex},
            opex {opex},
            days_to_investigate {days_to_investigate},
            days_to_procure {days_to_procure},
            days_to_repair {days_to_repair}{}

    int id {};
    int component_id {};
    std::string name {};
    std::string description {};
    std::string tag {};
    double capex {};
    double opex {};
    int days_to_investigate {};
    int days_to_procure {};
    int days_to_repair {};

    std::vector<std::string> toString(){
        return {std::to_string(id),
                std::to_string(component_id), name, description, tag,
                std::to_string(capex),
                std::to_string(opex),
                std::to_string(days_to_investigate),
                std::to_string(days_to_procure),
                std::to_string(days_to_repair)};

    }




};

#endif //ATVALUE_FAILUREMODEDETAIL_H
