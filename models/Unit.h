//
// Created by Paul on 2021/12/28.
//

#ifndef TREE_UNIT_H
#define TREE_UNIT_H


#include <string>
#include <vector>
#include "FailureMode.h"

using namespace std;

class Unit {
    int id_;
    string name_;
    weak_ptr<Unit> parent_;
    vector<shared_ptr<Unit>> children_;
    vector<unique_ptr<FailureMode>> failure_modes_;
    double capacity_;

public:
    friend ostream& operator<<(ostream& os, const Unit& unit);

    Unit() = delete;
    Unit(int id, string name, double capacity=0, unsigned children=0);

    void setParent(weak_ptr<Unit> parent_ptr);
    int getParentId() const;
    void addChild(const shared_ptr<Unit>& child);
    bool isRoot() const;
    int getId() const;
    unsigned countOfChildren() const;
    string getName() const;
    double getCapacity() const;
    void addFailureMode(unique_ptr<FailureMode> mode);
};


#endif //TREE_UNIT_H
