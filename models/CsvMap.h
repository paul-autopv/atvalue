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
    unsigned days_installed {4};
};

struct FailureModes {
    unsigned id {0};
    unsigned unit_id {1};
    unsigned name {2};
    unsigned description {3};
    unsigned tag {4};
    unsigned probability {5};
    unsigned a {6};
    unsigned b {7};

};

#endif //TREE_CSVMAP_H
