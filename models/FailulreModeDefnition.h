//
// Created by Paul on 2022/01/14.
//

#ifndef TREE_FAILULREMODEDEFNITION_H
#define TREE_FAILULREMODEDEFNITION_H

#include <string>

struct WeibullDefinition {
    unsigned id;
    unsigned unit_id;
    std::string name;
    std::string description;
    std::string tag;
    double alpha;
    double beta;
};

#endif //TREE_FAILULREMODEDEFNITION_H
