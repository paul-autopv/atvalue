//
// Created by Paul on 2022/01/17.
//

#include "Simulator.h"

Simulator::Simulator(int simulations, std::unique_ptr<Facility> facility) :
    simulations_ {simulations < 0 ? 0 : simulations},
    facility_ {std::move(facility)} {

}

void Simulator::run() {

    vector<std::thread> threads;
    threads.reserve(simulations_);
    for (int i = 0; i < simulations_; ++i) {
        threads.emplace_back(printProgress,i);
    }
    for (int i = 0; i < simulations_; ++i) {
        threads[i].join();
    }
    std::cout << "Done" << std::endl;
}

void Simulator::printProgress(int id){
    if (id == 5)
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    cout << "id: " << id << endl;
}
