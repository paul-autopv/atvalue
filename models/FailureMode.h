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
    FailureModeDetail failureModeDetail_;
    unique_ptr<IProbability> distribution_;

public:

    FailureMode() = delete;
    FailureMode(FailureModeDetail  detail, unique_ptr<IProbability> distribution);

    int getId() const;
    int getUnitId() const;
    string getDescription() const;
    string getName() const;
    string getTag() const;

    FailureModeDetail getFailureModeDetail();
    double getFailureProbability(const int &day) const;

};


#endif //ATVALUE_FAILUREMODE_H
