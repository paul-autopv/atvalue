//
// Created by Paul.Nel on 22/02/2022.
//

#ifndef ATVALUE_OUTAGECOST_H
#define ATVALUE_OUTAGECOST_H


class OutageCost {
public:

    OutageCost() : OutageCost(0, 0){};
    explicit OutageCost(double capex = 0, double opex = 0): capex_ {capex}, opex_ {opex}{}

    double capex() const{ return capex_;}
    double opex() const{ return opex_;}
    double total() const{ return opex() + capex();}

private:
    double capex_ {0};
    double opex_ {0};
};


#endif //ATVALUE_OUTAGECOST_H
