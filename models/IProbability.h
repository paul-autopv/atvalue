//
// Created by Paul on 2022/01/01.
//

#ifndef ATVALUE_IPROBABILITY_H
#define ATVALUE_IPROBABILITY_H

class IProbability{
public:
    virtual double getProbability(const int &day) = 0;
    virtual void resetProbability(const int &day) = 0;
};

#endif //ATVALUE_IPROBABILITY_H
