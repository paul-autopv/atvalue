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
    default_random_engine engine {};
    uniform_int_distribution distribution {0, 1000};
    auto likelihood = [&distribution, &engine](){ return (double)distribution(engine)/1000; };

    for (int day = 0; day < duration_; ++day) {
        auto risksForToday = facility_->getShuffledFailureModes();
        for (auto &risk : risksForToday){
            auto probability = likelihood();
            cout <<
            "Facility: " << facility_->getFailureProbability(risk, day) <<
            " probability: " <<  probability <<
            " occurred: " << hasOccurredFailure(day, risk, probability) << endl;
        }
    }

    return 0;

}

bool ProductionCycle::hasOccurredFailure(int day, const int &risk, double probability) {
    return facility_->getFailureProbability(risk, day) > probability;
}

#pragma clang diagnostic pop