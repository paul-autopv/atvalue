//
// Created by Paul on 2022/01/17.
//
#include "Simulator.h"
#include "ProductionCycle.h"

#include <utility>
#include "ProductionCycle.h"


Simulator::Simulator(const int &simulations, const int &duration, InputMap failures, InputMap structure) :
    simulations_ {simulations < 0 ? 0 : simulations},
    duration_ {duration},
    failures_ {std::move(failures)},
    structure_ {std::move(structure)}{

    if (simulations_ <= 0) {
        throw invalid_argument("Simulation duration must be larger than 0.");
    }
    if (duration_ <= 0) {
        throw invalid_argument("Number of simulations must be larger than 0.");
    }
}


void Simulator::run() const {

    using Task_type = vector<int>();

    vector<std::thread> threads;
    threads.reserve(simulations_);

    // define functors
    vector<ProductionCycle> productionCycles(simulations_);
    for (auto i = 0; i < simulations_; ++i){
        productionCycles[i] = ProductionCycle(duration_);

    }

    // define tasks
    deque<packaged_task<Task_type>> productionCycleTasks;
    for (auto i = 0; i < simulations_; ++i){
        packaged_task<Task_type> productionCyleTask {(productionCycles[i]) };
        productionCycleTasks.push_back(move(productionCyleTask));
    }

    // define futures
    vector<future<TypeRegister>> futures(simulations_);
    for (auto i = 0; i < simulations_; ++i){
        futures[i] = productionCycleTasks[i].get_future();
    }

    // define threads
    int i {0};
    while (!productionCycleTasks.empty()){
        auto task = move(productionCycleTasks.front());
        productionCycleTasks.pop_front();
        thread t {move(task)};
        t.detach();
        ++i;
    }

    TypeRegister accumulator;
    accumulator.resize(duration_);
    for (auto future = 0; future < simulations_; ++future){
        auto future_register = futures[future].get();
        accumulator = sumRegister(accumulator, future_register);
    }

    long sum {0};
    for (int j = 0; j < duration_; ++j) {
        sum += accumulator[j];
    }
    std::cout << "Sum of all elements: " << sum << endl;
    std::cout << "Done" << std::endl;
}

void Simulator::run_single() const{

    for (int i = 0; i < simulations_; ++i) {
        auto progress = ProductionCycle(duration_);
        progress();
    }
}

Simulator::TypeRegister& Simulator::sumRegister(Simulator::TypeRegister &a, Simulator::TypeRegister &b) {

    if (a.size() != b.size())
        throw out_of_range("Registers are of different length");

    for (int i = 0; i < a.size(); ++i) {
        a[i] += b[i];
    }
    return a;
}


