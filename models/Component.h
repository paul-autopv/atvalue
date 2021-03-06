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
    vector<bool> available_days;
    vector<bool> online_days;
    vector<double> capacity_loss_;
    int simulation_duration_ {};
    int day_installed_{};
    double active_capacity_ {0};

    void setCapacity(const int &start, const int &outage_duration, const double &value);

public:
    friend ostream& operator<<(ostream& os, const Component& unit);

    Component() = delete;
    Component(const Component&) = delete;
    Component(int id, string name, const int &simulation_duration, int days_installed,
              vector<shared_ptr<FailureMode>> failure_modes, double capacity, int children);

    bool isOnline(const int &day) const;
    void setParent(const shared_ptr<Component>& parent_ptr);
    int getParentId() const;
    void addChild(const shared_ptr<Component>& child);
    int getId() const;

    void setDayInstalled(const int& day);
    void scheduleOutage(const int &start, const int &outage_duration);
    bool isAvailable(const int &day) const;
    vector<bool> getAvailability();
    vector<double> getCapacityLoss();
    double getCapacity();

    void scheduleCapacityLoss(const int &start, const int &outage_duration);
};


#endif //ATVALUE_COMPONENT_H
