//
// Created by Paul on 2021/12/28.
//

#ifndef ATVALUE_COMPONENT_H
#define ATVALUE_COMPONENT_H


#include <string>
#include <vector>
#include "FailureMode.h"
#include "enums/ShutdownCode.h"

using namespace std;

class Component {

private:
    int id_{};
    string name_;
    weak_ptr<Component> parent_;
    vector<shared_ptr<Component>> children_;
    vector<shared_ptr<FailureMode>> failure_modes_;
    int days_installed_{};
    double capacity_{};
    bool is_online_ {true};
    bool is_available_ {true};


public:
    friend ostream& operator<<(ostream& os, const Component& unit);

    Component() = delete;
    Component(const Component&) = delete;
    Component(int id, string name, int days_installed, vector<shared_ptr<FailureMode>> failure_modes, double capacity= 0, int children= 0);

    bool isAvailable() const;
    bool isOnline() const;
    void setParent(weak_ptr<Component> parent_ptr);
    int getParentId() const;
    void addChild(const shared_ptr<Component>& child);
    void addFailureMode(unique_ptr<FailureMode> mode);
    bool isRoot() const;
    int getId() const;
    int countOfChildren() const;
    string getName() const;
    double getCapacity() const;
    int getDaysInstalled() const;

    void shutdown(ShutdownCode code = ShutdownCode::unplanned);
    void startup();

};


#endif //ATVALUE_COMPONENT_H
