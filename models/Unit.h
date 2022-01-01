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
    shared_ptr<Unit> parent_;
    vector<weak_ptr<Unit>> children_;
    vector<FailureMode> failure_modes_;
    double capacity;
public:
    double getCapacity() const;

    void setCapacity(double capacity);


public:
    friend ostream& operator<<(ostream& os, const Unit& unit);

    Unit() = delete;
    Unit(int id, string name);

    void setParent(shared_ptr<Unit>);
    int getParentId() const;
    void addChild(const shared_ptr<Unit>& child);
    bool isRoot() const;
    int getId() const;
    unsigned countOfChildren() const;
    string getName() const;

    void addFailureMode(FailureMode mode);
};


#endif //TREE_UNIT_H
