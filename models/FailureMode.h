//
// Created by Paul on 2022/01/01.
//

#ifndef TREE_FAILUREMODE_H
#define TREE_FAILUREMODE_H


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
    FailureMode(const FailureMode &other);
    FailureMode(int id, int unit_id, string name, string description, string tag, unique_ptr<IProbability> distribution);
    FailureMode& operator=(const FailureMode& other);

    int getId() const;
    int getUnitId() const;
    bool hasOccurred(const double &probability, const int &day) const;

};


#endif //TREE_FAILUREMODE_H
