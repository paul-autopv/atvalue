//
// Created by Paul on 2022/01/01.
//

#ifndef TREE_IPROBABILITY_H
#define TREE_IPROBABILITY_H

class IProbability{
protected:
    virtual double getProbability(const int &day) = 0;
};

#endif //TREE_IPROBABILITY_H
