//
// Created by Paul on 2022/01/17.
//
#include "Simulator.h"
#include "Register.h"



Simulator::Simulator(int simulations, std::unique_ptr<Facility> facility, int duration) :
    simulations_ {simulations < 0 ? 0 : simulations},
    facility_ {std::move(facility)},
    duration_ {duration} {}

void Simulator::run() {

    using Task_type = vector<int>();

    vector<std::thread> threads;
    threads.reserve(simulations_);

    // define functors
    vector<Register> printProgress(simulations_);
    for (auto i = 0; i < simulations_; ++i){
        printProgress[i] = Register(duration_);
    }

    // define tasks
    deque<packaged_task<Task_type>> packagedTasks;
    for (auto i = 0; i < simulations_; ++i){
        packaged_task<Task_type> task { (printProgress[i]) };
        packagedTasks.push_back(move(task));
    }

    // define futures
    vector<future<TypeRegister>> futures(simulations_);
    for (auto i = 0; i < simulations_; ++i){
        futures[i] = packagedTasks[i].get_future();
    }

    // define threads
    int i {0};
    while (!packagedTasks.empty()){
        auto task = move(packagedTasks.front());
        packagedTasks.pop_front();
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
    std::cout << "Sum of all elements: " << endl;
    std::cout << "Done" << std::endl;
}

void Simulator::run_single(){

    for (int i = 0; i < simulations_; ++i) {
        auto progress = Register(duration_);
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


