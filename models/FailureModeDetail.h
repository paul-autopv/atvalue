//
// Created by Paul on 2/22/22.
//

#ifndef ATVALUE_FAILUREMODEDETAIL_H
#define ATVALUE_FAILUREMODEDETAIL_H

#include <string>
#include <utility>

struct FailureModeDetail{
    FailureModeDetail() = default;
    FailureModeDetail(int id, int unit_id, std::string name, std::string description, std::string tag) :
        id {id},
        unit_id {unit_id},
        name {std::move(name)},
        description {std::move(description)},
        tag {std::move(tag)}{}

    int id {};
    int unit_id {};
    std::string name {};
    std::string description {};
    std::string tag {};
};

#endif //ATVALUE_FAILUREMODEDETAIL_H
