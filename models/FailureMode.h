//
// Created by Paul on 2022/01/01.
//

#ifndef ATVALUE_FAILUREMODE_H
#define ATVALUE_FAILUREMODE_H


#include <string>
#include <memory>
#include "IProbability.h"
#include "FailureModeDetail.h"

using namespace std;

class FailureMode {

public:

    FailureMode() = delete;
    FailureMode(FailureModeDetail  detail, unique_ptr<IProbability> distribution);

    int getId() const;
    int getComponentId() const;
    double getCapex() const;
    double getOpex() const;
    int getDaysToInvestigate() const;
    int getDaysToProcure() const;
    int getDaysToRepair() const;

    FailureModeDetail getFailureModeDetail();
    void updateFailureModeDetail(const FailureModeDetail &detail);
    double getFailureProbability(const int &day) const;

private:
    FailureModeDetail failureModeDetail_;
    unique_ptr<IProbability> distribution_;

};


#endif //ATVALUE_FAILUREMODE_H
