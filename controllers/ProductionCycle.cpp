#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-pass-by-value"
//
// Created by Paul on 2/20/22.
//

#include "ProductionCycle.h"

ProductionCycle::ProductionCycle() : ProductionCycle(0, InputMap(), InputMap()) {}

ProductionCycle::ProductionCycle(const int &duration, const InputMap &structure,const InputMap &failures) :
        duration_ {duration}, structure_ {structure}, failures_ {failures}{
    facility_ = make_shared<Facility>();
    facility_->buildFacility(structure_, failures_);
};


int ProductionCycle::operator()() {
    const int max {1'000'000};
    default_random_engine engine {};
    uniform_int_distribution distribution {0, max};
    auto likelihood = [&distribution, &engine](){ return (double)distribution(engine)/max; };

    for (int day = 0; day < duration_; ++day) {
        auto risksForToday = facility_->getShuffledFailureModes();
        for (auto &risk : risksForToday){
            auto probability = likelihood();
            if (hasOccurredFailure(day, risk, probability)){
                auto event = facility_->getFailureModeDetail(risk);
                incidentRegister_.insert(pair<int, vector<string>>(day, event));
            }
        }
    }

    return 0;

}

bool ProductionCycle::hasOccurredFailure(const int &day, const int &risk, const double &probability) {
    return facility_->getFailureModeProbability(risk, day) > probability;
}

#pragma clang diagnostic pop