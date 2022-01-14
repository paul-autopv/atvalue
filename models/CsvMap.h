//
// Created by Paul on 2022/01/13.
//

#ifndef TREE_CSVMAP_H
#define TREE_CSVMAP_H

struct StationFields {
    unsigned id {0};
    unsigned parent_id {1};
    unsigned name {2};
    unsigned capacity {3};
};

struct FailureModes {
    unsigned id {0};
    unsigned unit_id {1};
    unsigned name {2};
    unsigned description {3};
    unsigned tag {4};
    unsigned probability {5};
    unsigned alpha {6};
    unsigned beta {7};
    unsigned days_installed {8};
    unsigned days_should_fail {9};
    unsigned days_will_fail {10};
};

#endif //TREE_CSVMAP_H
