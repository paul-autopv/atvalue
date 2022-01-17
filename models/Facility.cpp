#include "Facility.h"

void Facility::buildFacility(const InputMap &unit_map, const InputMap &failure_map) {
    auto family_tree= childCounter(unit_map);
    auto failure_modes = unitFailureModes(failure_map);

    for (auto iter {cbegin(unit_map)}; iter != cend(unit_map); ++iter) {
        vector<shared_ptr<FailureMode>> failures;
        auto is_root = (iter == cbegin(unit_map));
        auto unit_record = iter->second;
        auto unit_failures = (*failure_modes)[iter->first];

        for (auto failure : unit_failures){
            FailureModeFields fields;
            auto failure_parameters = failure_map.at(failure);
            auto probability = getProbability(failure_parameters, failure_parameters[fields.probability]);
            auto failure_mode = make_shared<FailureMode>(
                    FailureMode(stoi(failure_parameters[fields.id]),
                                failure_parameters[fields.name],
                                failure_parameters[fields.description],
                                failure_parameters[fields.tag],
                                move(probability)));
            failure_map_.emplace(failure_mode->getId(), failure_mode);
            failures.push_back(failure_mode);
        }
        loadUnit(unit_record, unit_map, family_tree, move(failures), is_root);
    }
}

unique_ptr<IProbability> Facility::getProbability(const vector<string> &failure_mode,
                                                  const basic_string<char, char_traits<char>, allocator<char>> &probability_type) {
    FailureModeFields fields;
    auto a = stod(failure_mode[fields.a]);
    auto b = stod(failure_mode[fields.b]);
    if (probability_type == "weibull")
        return make_unique<WeibullProbability>(a, b);
    return make_unique<TriangularProbability>(TriangularProbability((unsigned) a, (unsigned) b));
}

FamilyTree Facility::childCounter(const InputMap& unit_map) {

    StationFields fields;
    auto children = std::make_unique<std::map<unsigned, unsigned>>();

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
    auto failures = std::make_unique<std::unordered_map<unsigned, std::vector<unsigned>>>();

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

unsigned Facility::unitCount() const {
    return unit_map_.size();
}


int Facility::getParentIdOfUnit(int unit_id) const {
    if(!isInUnitMap(unit_id)){
        std::string message = "Current unit map does not contain unit with provided id ";
        throw std::invalid_argument(message);
    }
    return unit_map_.at(unit_id)->getParentId();
}

unsigned Facility::getChildrenCountForUnit(int unit_id) const {
    if(!isInUnitMap(unit_id)){
        std::string message = "Current unit map does not contain unit with provided id";
        throw std::invalid_argument(message);
    }    return unit_map_.at(unit_id)->countOfChildren();
}

bool Facility::isInUnitMap(int id) const{
    return unit_map_.find(id) != unit_map_.end();
}

unsigned int Facility::childrenCount(const FamilyTree& family_tree, unsigned int unit_id) {
    if (!family_tree->empty() && (*family_tree)[unit_id]){
        return family_tree->find(unit_id)->second;
    }
    return 0;
}

unsigned Facility::failureCount() const {
    return failure_map_.size();
}
