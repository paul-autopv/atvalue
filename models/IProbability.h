//
// Created by Paul on 2022/01/01.
//

#ifndef ATVALUE_IPROBABILITY_H
#define ATVALUE_IPROBABILITY_H

class IProbability{
public:
    virtual double getProbability(const int &day) = 0;
    virtual void setParameters(const double &a, const double &b, const double &c = 0)  = 0;
};

#endif //ATVALUE_IPROBABILITY_H
