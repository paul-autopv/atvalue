#include <algorithm>
#include "Facility.h"

void Facility::buildFacility(const InputMap &component_map, const InputMap &failure_map) {
    StationFields fields;
    auto structure= childCounter(component_map);
    auto failure_modes = getAllComponentFailureModes(failure_map);

    for (auto iter = component_map.begin(); iter != component_map.end(); ++iter) {
        auto component = iter->first;
        auto component_record = iter->second;
        auto component_installed = stoi(component_record[fields.days_installed]);
        auto is_root = (iter == component_map.begin());
        auto failures = getFailureModesForComponent(failure_map, (*failure_modes)[component], component_installed);
        registerComponentWithFacility(component_record, component_map, structure, failures, is_root);
        registerFailureModesWithFacility(failures);
    }
}

vector<shared_ptr<FailureMode>>
Facility::getFailureModesForComponent(const InputMap &failure_map, vector<int> &component_failures,
                                      int component_installed) {

    FailureModeFields fields;
    vector<shared_ptr<FailureMode>> failures;

    for (auto failure : component_failures){
        auto failure_parameters = failure_map.at(failure);
        auto probability_distribution = getProbabilityDistribution(
                failure_parameters,
                failure_parameters[fields.probability], component_installed);
        auto failure_mode_detail = FailureModeDetail(
                stoi(failure_parameters[fields.id]),
                stoi(failure_parameters[fields.component_id]),
                failure_parameters[fields.name],
                failure_parameters[fields.description],
                failure_parameters[fields.tag],
                getScope(failure_parameters[fields.scope]),
                stod(failure_parameters[fields.capex]),
                stod(failure_parameters[fields.opex]),
                stoi(failure_parameters[fields.days_to_investigate]),
                stoi(failure_parameters[fields.days_to_procure]),
                stoi(failure_parameters[fields.days_to_repair]));
        auto failure_mode = make_shared<FailureMode>(FailureMode(
                failure_mode_detail,
                move(probability_distribution)));
        failures.push_back(failure_mode);
    }
    return failures;
}

unique_ptr<IProbability>
Facility::getProbabilityDistribution(const vector<string> &failure_mode, const string &probability_type,
                                     int component_installed) {
    FailureModeFields fields;
    if (probability_type == "weibull"){
        return make_unique<WeibullProbability>(
                stod(failure_mode[fields.a]),
                stod(failure_mode[fields.b]));
    }
    return make_unique<TriangularProbability>(TriangularProbability(
            -component_installed,
            stoi(failure_mode[fields.a]),
            stoi(failure_mode[fields.b])));
}

FamilyTree Facility::childCounter(const InputMap& component_map) {

    StationFields fields;
    auto children = std::make_unique<std::map<int, int>>();

    if (!component_map.empty()) {
        for (auto iter{cbegin(component_map)}; iter != cend(component_map); ++iter) {
            auto parent_id = stoi(iter->second[fields.parent_id]);
            if (children == nullptr || children->find(parent_id) == children->end())
                (*children)[parent_id] = 0;
            (*children)[parent_id]++;
        }
    }
    return children;
}

std::unique_ptr<ComponentFailureModes> Facility::getAllComponentFailureModes(const InputMap& failure_mode_map) {

    FailureModeFields fields;
    auto failures = std::make_unique<std::unordered_map<int, std::vector<int>>>();

    if(!failure_mode_map.empty()){
        for (auto iter{failure_mode_map.begin()}; iter != failure_mode_map.end(); ++iter) {
            auto unit_id = stoi(iter->second[fields.component_id]);
            auto failure_id = stoi(iter->second[fields.id]);
            (*failures)[unit_id].push_back(failure_id);
        }
    }
    return failures;
}

void Facility::registerComponentWithFacility(const vector<string> &component_detail, const InputMap &component_map, FamilyTree &structure,
                                             vector<shared_ptr<FailureMode>> failures, bool isRoot) {

    StationFields fields;

    auto id = stoi(component_detail[fields.id]);
    auto name = component_detail[fields.name];
    auto capacity = stod(component_detail[fields.capacity]);
    auto days_installed = stoi(component_detail[fields.days_installed]);
    auto children = childrenCount(structure, id);
    auto parent_id = (isRoot) ? -1 : stoi(component_detail[fields.parent_id]);
    auto component = make_unique<Component>(id, name, days_installed, move(failures), capacity, children);
    auto component_ptr = registerComponent(component);
    linkParentChildNodes(component_ptr, parent_id);

    cout << "Added " << name << " (id: " << id << ")" << endl;
}

void Facility::linkParentChildNodes(const std::shared_ptr<Component>& component_ptr, int parent_id) {

    if (parent_id > 0){
        auto parent_ptr = getParent(parent_id);
        component_ptr->setParent(weak_ptr<Component>(parent_ptr));
        parent_ptr->addChild(component_ptr);
    }
}

shared_ptr<Component> Facility::registerComponent(unique_ptr<Component> &component) {
    auto  unit_ptr = shared_ptr<Component>(move(component));
    component_map_.emplace(unit_ptr->getId(), unit_ptr);
    return unit_ptr;
}

shared_ptr<Component> Facility::getParent(int parent_id) {
    if (!isInComponentMap(parent_id)) {
        std::string message = "Current unit map does not contain unit with parent_id";
        throw std::invalid_argument( message );
    }
    return {component_map_.at(parent_id)};
}

int Facility::componentCount() const {
    return component_map_.size();
}


bool Facility::isInComponentMap(int id) const{
    return component_map_.find(id) != component_map_.end();
}

int Facility::childrenCount(const FamilyTree& family_tree, int component_id) {
    if (!family_tree->empty() && (*family_tree)[component_id]){
        return family_tree->find(component_id)->second;
    }
    return 0;
}

int Facility::failureCount() const {
    return failure_map_.size();
}

void Facility::registerFailureModesWithFacility(const vector<shared_ptr<FailureMode>>& failure_modes) {
    for (const auto& failure : failure_modes) {
        auto component_id = failure->getComponentId();
        if (component_map_.find(component_id) != component_map_.end()){
            failure_map_.emplace(failure->getId(), failure);
        }
        else{
            cout << "FailureMode with id " << failure->getId() <<
            " not registered because component with id " << component_id <<
            " not found in component map." << endl;
        }
    }
}

vector<int> Facility::getShuffledFailureModes() {
    vector<int> failureIds;

    for (auto & it : failure_map_) {
        failureIds.push_back(it.first);
    }

    std::random_device randomDevice;
    std::default_random_engine randomEngine(randomDevice());
    shuffle(failureIds.begin(), failureIds.end(), randomEngine);
    return failureIds;
}

double Facility::getFailureModeProbability(const int &failureId, const int &day) {
    return failure_map_.at(failureId)->getFailureProbability(day);
}

FailureModeDetail Facility::getFailureModeDetail(const int &failureId) {
    auto id = to_string(failureId);
    return failure_map_.at(failureId)->getFailureModeDetail();

}

shared_ptr<Component> Facility::getComponentPtr(const int &component_id) {
    auto component = component_map_.at(component_id);
    return { component };
}

FailureScope Facility::getScope(const string &scope) {
    if (scope == "all")
        return FailureScope::all;
    if (scope == "parent")
        return FailureScope::parent;
    return FailureScope::cascade;
}
