#include <algorithm>
#include "Facility.h"

void Facility::buildFacility(const InputMap &component_map, const InputMap &failure_map) {
    auto family_tree= childCounter(component_map);
    auto failure_modes = componentFailureModes(failure_map);

    for (auto iter {cbegin(component_map)}; iter != cend(component_map); ++iter) {
        auto is_root = (iter == cbegin(component_map));
        auto unit_record = iter->second;
        auto failures = getFailureModes(failure_map, (*failure_modes)[iter->first]);
        registerFailureModes(failures);
        loadComponent(unit_record, component_map, family_tree, move(failures), is_root);
    }
}

vector<shared_ptr<FailureMode>> Facility::getFailureModes(const InputMap &failure_map, vector<int> &component_failures) {
    vector<shared_ptr<FailureMode>> failures;
    for (auto failure : component_failures){
        FailureModeFields fields;
        auto failure_parameters = failure_map.at(failure);
        auto probability_distribution = getProbabilityDistribution(failure_parameters, failure_parameters[fields.probability]);
        auto failure_mode = make_shared<FailureMode>(
                FailureMode(stoi(failure_parameters[fields.id]),
                            stoi(failure_parameters[fields.unit_id]),
                            failure_parameters[fields.name],
                            failure_parameters[fields.description],
                            failure_parameters[fields.tag],
                            move(probability_distribution)));
        failures.push_back(failure_mode);
    }
    return failures;
}


unique_ptr<IProbability> Facility::getProbabilityDistribution(const vector<string> &failure_mode, const string &probability_type) {
    FailureModeFields fields;
    if (probability_type == "weibull"){
        auto a = stod(failure_mode[fields.a]);
        auto b = stod(failure_mode[fields.b]);
        return make_unique<WeibullProbability>(a, b);
    }
    auto a = stoi(failure_mode[fields.a]);
    auto b = stoi(failure_mode[fields.b]);
    auto c = stoi(failure_mode[fields.c]);
    return make_unique<TriangularProbability>(TriangularProbability(a,b, c));
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

std::unique_ptr<ComponentFailureModes> Facility::componentFailureModes(const InputMap& failure_mode_map) {

    FailureModeFields fields;
    auto failures = std::make_unique<std::unordered_map<int, std::vector<int>>>();

    if(!failure_mode_map.empty()){
        for (auto iter{cbegin(failure_mode_map)}; iter != cend(failure_mode_map); ++iter) {
            auto unit_id = stoi(iter->second[fields.unit_id]);
            auto failure_id = stoi(iter->second[fields.id]);
            (*failures)[unit_id].push_back(failure_id);
        }
    }
    return failures;
}

void Facility::loadComponent(const vector<string> &component, const InputMap &component_map, FamilyTree &family_tree,
                             vector<shared_ptr<FailureMode>> failures, bool isRoot) {

    StationFields fields;

    auto id = stoi(component[fields.id]);
    auto name = component[fields.name];
    auto capacity = stod(component[fields.capacity]);
    auto days_installed = stoi(component[fields.days_installed]);
    auto children = childrenCount(family_tree, id);
    auto parent_id = (isRoot) ? -1 : stoi(component[fields.parent_id]);
    addComponent(make_unique<Component>(id, name, days_installed, move(failures), capacity, children), parent_id);

    cout << "Added " << name << " (id: " << id << ")" << endl;
}

void Facility::addComponent(std::unique_ptr<Component> component, int parent_id) {
    auto unit_ptr = registerComponent(component);

    if (parent_id > 0){
        auto parent_ptr = getParent(parent_id);
        unit_ptr->setParent(weak_ptr<Component>(parent_ptr));
        parent_ptr->addChild(unit_ptr);
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

void Facility::registerFailureModes(const vector<shared_ptr<FailureMode>>& failure_modes) {
    for (const auto& failure : failure_modes) {
        failure_map_.emplace(failure->getId(), failure);
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

vector<string> Facility::getFailureModeDetail(const int &failureId) {
    auto id = to_string(failureId);
    auto unit = to_string(failure_map_.at(failureId)->getUnitId());
    auto name = failure_map_.at(failureId)->getName();
    auto description = failure_map_.at(failureId)->getDescription();
    auto tag = failure_map_.at(failureId)->getTag();
    return {id, unit, name, description, tag};
}
