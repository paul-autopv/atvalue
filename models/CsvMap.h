//
// Created by Paul on 2022/01/13.
//

#ifndef ATVALUE_CSVMAP_H
#define ATVALUE_CSVMAP_H

struct StationFields {
    unsigned id {0};
    unsigned parent_id {1};
    unsigned name {2};
    unsigned capacity {3};
    unsigned days_installed {4};
};

struct FailureModeFields {
    unsigned id {0};
    unsigned component_id {1};
    unsigned name {2};
    unsigned description {3};
    unsigned tag {4};
    unsigned scope {5};
    unsigned days_to_investigate {6};
    unsigned days_to_procure {7};
    unsigned days_to_repair {8};
    unsigned capex {9};
    unsigned opex {10};
    unsigned probability {11};
    unsigned a {12};
    unsigned b {13};


};



#endif //ATVALUE_CSVMAP_H
