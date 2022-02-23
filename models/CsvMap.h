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
    unsigned unit_id {1};
    unsigned name {2};
    unsigned description {3};
    unsigned tag {4};
    unsigned days_to_investigate {5};
    unsigned days_to_procure {6};
    unsigned days_to_repair {7};
    unsigned capex {8};
    unsigned opex {9};
    unsigned probability {10};
    unsigned a {11};
    unsigned b {12};
    unsigned c {13};

};



#endif //ATVALUE_CSVMAP_H
