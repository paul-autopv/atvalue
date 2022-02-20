#include "Facility.h"

void Facility::buildFacility(const InputMap &unit_map, const InputMap &failure_map) {
    auto family_tree= childCounter(unit_map);
    auto failure_modes = unitFailureModes(failure_map);

    for (auto iter {cbegin(unit_map)}; iter != cend(unit_map); ++iter) {
        auto is_root = (iter == cbegin(unit_map));
        auto unit_record = iter->second;
        auto failures = getFailureModes(failure_map, (*failure_modes)[iter->first]);
        registerFailureModes(failures);
        loadUnit(unit_record, unit_map, family_tree, move(failures), is_root);
    }
}

vector<shared_ptr<FailureMode>> Facility::getFailureModes(const InputMap &failure_map, vector<int> &unit_failures) {
    vector<shared_ptr<FailureMode>> failures;
    for (auto failure : unit_failures){
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
    auto a = stod(failure_mode[fields.a]);
    auto b = stod(failure_mode[fields.b]);
    if (probability_type == "weibull")
        return make_unique<WeibullProbability>(a, b);
    return make_unique<TriangularProbability>(TriangularProbability(0, (int) a, (int) b));
}

FamilyTree Facility::childCounter(const InputMap& unit_map) {

    StationFields fields;
    auto children = std::make_unique<std::map<int, int>>();

    if (!unit_map.empty()) {
        for (auto iter{cbegin(unit_map)}; iter != cend(unit_map); ++iter) {
            auto parent_id = stoi(iter->second[fields.parent_id]);
            if (children == nullptr || children->find(parent_id) == children->end())
                (*children)[parent_id] = 0;
            (*children)[parent_id]++;
        }
    }
    return children;
}

std::unique_ptr<UnitFailureModes> Facility::unitFailureModes(const InputMap& failure_mode_map) {

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

void Facility::loadUnit(const vector<string> &unit, const InputMap &unit_map, FamilyTree &family_tree,
                        vector<shared_ptr<FailureMode>> failures, bool isRoot) {

    StationFields fields;

    auto id = stoi(unit[fields.id]);
    auto name = unit[fields.name];
    auto capacity = stod(unit[fields.capacity]);
    auto days_installed = stoi(unit[fields.days_installed]);
    auto children = childrenCount(family_tree, id);
    auto parent_id = (isRoot) ? -1 : stoi(unit[fields.parent_id]);
    addUnit(make_unique<Unit>(id, name, days_installed, move(failures), capacity, children), parent_id);

    cout << "Added " << name << " (id: " << id << ")" << endl;
}

void Facility::addUnit(std::unique_ptr<Unit> unit, int parent_id) {
    auto unit_ptr = registerUnit(unit);

    if (parent_id > 0){
        auto parent_ptr = getParent(parent_id);
        unit_ptr->setParent(weak_ptr<Unit>(parent_ptr));
        parent_ptr->addChild(unit_ptr);
    }
}

shared_ptr<Unit> Facility::registerUnit(unique_ptr<Unit> &unit) {
    auto  unit_ptr = shared_ptr<Unit>(move(unit));
    unit_map_.emplace(unit_ptr->getId(), unit_ptr);
    return unit_ptr;
}

shared_ptr<Unit> Facility::getParent(int parent_id) {
    if (!isInUnitMap(parent_id)) {
        std::string message = "Current unit map does not contain unit with parent_id";
        throw std::invalid_argument( message );
    }
    return {unit_map_.at(parent_id)};
}

int Facility::unitCount() const {
    return unit_map_.size();
}


bool Facility::isInUnitMap(int id) const{
    return unit_map_.find(id) != unit_map_.end();
}

int Facility::childrenCount(const FamilyTree& family_tree, int unit_id) {
    if (!family_tree->empty() && (*family_tree)[unit_id]){
        return family_tree->find(unit_id)->second;
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
    cout << "test" << endl;

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
