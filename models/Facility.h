//
// Created by Paul on 2021/12/31.
//

#ifndef ATVALUE_FACILITY_H
#define ATVALUE_FACILITY_H

#include <memory>
#include <map>
#include <unordered_map>
#include <iostream>
#include <random>

#include "Component.h"
#include "CsvMap.h"
#include "../probabilities/TriangularProbability.h"

using namespace std;

using FamilyTree = std::shared_ptr<std::map<int, int>>;
using InputMap = std::map<int, std::vector<std::string>>;
using FailureMap = unordered_map<int, shared_ptr<FailureMode>>;
using ComponentMap = unordered_map<int, shared_ptr<Component>>;
using ComponentFailureModes = std::unordered_map<int, std::vector<int>>;
using IncidentRegister = map<int, vector<string>>;

class Facility {

public:
    Facility() = default;

    explicit Facility(int duration) : simulation_duration_ {duration} {};

    void buildFacility(const InputMap &component_map, const InputMap &failure_map);
    vector<int> getShuffledFailureModeIds();

    double getFailureModeProbability(const int &failureId, const int &day);
    FailureModeDetail getFailureModeDetail(const int &failureId);
    void resetFailureModeProbability(const int &day, const int &failure_mode_id);

    unsigned long failureCount() const;
    shared_ptr<Component> getComponentPtr(const int &component_id) const;
    shared_ptr<Component> getRootComponentPtr() const;

private:

    int simulation_duration_ {0};

    ComponentMap component_map_;

    FailureMap failure_map_;

    void linkParentChildNodes(const std::shared_ptr<Component>& component_ptr, int parent_id);

    void registerComponentWithFacility(const vector<string> &component_detail, const InputMap &component_map,
                                       FamilyTree &structure, vector<shared_ptr<FailureMode>> failures,
                                       bool isRoot, const int simulation_duration);

    shared_ptr<Component> registerComponent(shared_ptr<Component> component);

    bool isInComponentMap(int id) const;

    void registerFailureModesWithFacility(const vector<shared_ptr<FailureMode>>& failure_modes);

    vector<shared_ptr<FailureMode>>
    getFailureModesForComponent(const InputMap &failure_map, vector<int> &component_failures,
                                int component_installed);

    static std::unique_ptr<ComponentFailureModes> getAllComponentFailureModes(const InputMap& failure_mode_map);

    static FamilyTree childCounter(const InputMap& component_map);

    static int childrenCount(const FamilyTree & family_tree, int component_id);

    unique_ptr<IProbability>
    getProbabilityDistribution(const vector<string> &failure_mode, const string &probability_type,
                               int component_installed);

    shared_ptr<Component> getParent(int parent_id);
    FailureScope getScope(const string &scope);

};


#endif //ATVALUE_FACILITY_H
