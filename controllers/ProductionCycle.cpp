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

    for (int day = 0; day < duration_; ++day) {
        auto risksForToday = facility_->getShuffledFailureModes();
        for (auto &risk : risksForToday){
            cout << facility_->getFailureProbability(risk, day) <<endl;
        }
    }

    return 0;

}
#pragma clang diagnostic pop