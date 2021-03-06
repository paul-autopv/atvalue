//
// Created by Paul on 2/22/22.
//

#ifndef ATVALUE_FAILUREMODEDETAIL_H
#define ATVALUE_FAILUREMODEDETAIL_H

#include <string>
#include <utility>
#include <vector>
#include "enums/FailureScope.h"

class FailureModeDetail{

public:
    FailureModeDetail() = default;
    FailureModeDetail(int id, int component_id, std::string name, std::string description, std::string tag,
                      FailureScope scope, double capex, double opex, int days_to_investigate, int days_to_procure,
                      int days_to_repair) :
            id {id},
            component_id {component_id},
            name {std::move(name)},
            description {std::move(description)},
            tag {std::move(tag)},
            scope {scope},
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
    FailureScope scope{};
    double capex {};
    double opex {};
    int days_to_investigate {};
    int days_to_procure {};
    int days_to_repair {};

    std::vector<std::string> toString(){
        auto scope_string = getScopeString();
        return {std::to_string(id),
                std::to_string(component_id), name, description, tag,
                scope_string,
                std::to_string(capex),
                std::to_string(opex),
                std::to_string(days_to_investigate),
                std::to_string(days_to_procure),
                std::to_string(days_to_repair)};

    }

    std::string getScopeString() const {
        std::string scope_string;
        if (scope == FailureScope::component) {
            scope_string = "component";
        }
        if (scope == FailureScope::parent) {
            scope_string  = "parent";
        }
        if (scope == FailureScope::all) {
            scope_string ="all";
        }
        return scope_string;
    }


};

#endif //ATVALUE_FAILUREMODEDETAIL_H
