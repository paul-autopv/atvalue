//
// Created by Paul on 2022/01/01.
//

#ifndef ATVALUE_FAILUREMODE_H
#define ATVALUE_FAILUREMODE_H


#include <string>
#include <memory>
#include "IProbability.h"

using namespace std;

class FailureMode {
    int id_;
    int unit_id_;
    string name_;
    string description_;
    string tag_;
    unique_ptr<IProbability> distribution_;

public:

    FailureMode() = delete;
    FailureMode(int id, int unit_id, string name, string description, string tag, unique_ptr<IProbability> distribution);

    int getId() const;
    int getUnitId() const;
    string getDescription() const;
    string getName() const;
    string getTag() const;
    double getFailureProbability(const int &day) const;

};


#endif //ATVALUE_FAILUREMODE_H
