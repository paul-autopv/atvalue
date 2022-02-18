//
// Created by Paul on 2021/12/28.
//

#ifndef ATVALUE_UNIT_H
#define ATVALUE_UNIT_H


#include <string>
#include <vector>
#include "FailureMode.h"

using namespace std;

class Unit {
    int id_;
    string name_;
    weak_ptr<Unit> parent_;
    vector<shared_ptr<Unit>> children_;
    vector<shared_ptr<FailureMode>> failure_modes_;
    int days_installed_;
    double capacity_;

public:
    friend ostream& operator<<(ostream& os, const Unit& unit);

    Unit() = delete;
    Unit(int id, string name, int days_installed, vector<shared_ptr<FailureMode>> failure_modes, double capacity= 0, int children= 0);

    void setParent(weak_ptr<Unit> parent_ptr);
    int getParentId() const;
    void addChild(const shared_ptr<Unit>& child);
    void addFailureMode(unique_ptr<FailureMode> mode);
    bool isRoot() const;
    int getId() const;
    int countOfChildren() const;
    string getName() const;
    double getCapacity() const;
    int getDaysInstalled() const;
};


#endif //ATVALUE_UNIT_H
