//
// Created by Paul on 2022/01/17.
//
#include "Simulator.h"


Simulator::Simulator(const int &simulations, const int &duration, InputMap failures, InputMap structure) :
        simulations_ {simulations < 0 ? 0 : simulations},
        simulation_duration_ {duration},
        failures_ {std::move(failures)},
        structure_ {std::move(structure)}{

    if (simulations_ <= 0) {
        throw invalid_argument("Simulation duration must be larger than 0.");
    }
    if (simulation_duration_ <= 0) {
        throw invalid_argument("Number of simulations must be larger than 0.");
    }

    prepareOutputFiles();
}


void Simulator::run() const {

    vector<std::thread> threads;
    threads.reserve(simulations_);

    // define functors
    vector<ProductionManager> productionManagers(simulations_);
    for (auto i = 0; i < simulations_; ++i) {
        productionManagers[i] = ProductionManager(simulation_duration_, structure_, failures_);
    }

    // define tasks
    deque<packaged_task<Task_type>> productionManagerTasks;
    for (auto i = 0; i < simulations_; ++i) {
        packaged_task<Task_type> productionManagerTask{(productionManagers[i])};
        productionManagerTasks.push_back(move(productionManagerTask));
    }

    // define futures
    vector<future<ProductionReport>> futures(simulations_);
    for (auto i = 0; i < simulations_; ++i) {
        futures[i] = productionManagerTasks[i].get_future();
    }

    // define threads
    int i{0};
    while (!productionManagerTasks.empty()) {
        auto task = move(productionManagerTasks.front());
        productionManagerTasks.pop_front();
        thread t{move(task)};
        t.detach();
        ++i;
    }

    for (auto future = 0; future < simulations_; ++future) {
        auto report = futures[future].get();
        cout << "Writing register for simulation " << future << endl;
        reportToCsv(report);
    }
}

void Simulator::reportToCsv(ProductionReport report) const {

    auto incidents = report.getIncidents();
    reportIncidents(incidents);

    auto production_loss = report.getProductionLoss();
    reportProductionLoss(production_loss);

}

void Simulator::reportIncidents(vector<Incident> &report) {
    fstream out_file;

    out_file.open(incident_register_path_ + (string)"incidents.csv", ios_base::out | ios_base::app);
    int entry{1};
    for (auto &item: report) {
        out_file << entry;
        for (const auto& value: item.event) {
            out_file << "," << value;
        }
        out_file << endl;
        ++entry;
    }
}

void Simulator::reportProductionLoss(ProductionLoss &report) const {
    fstream out_file;

    out_file.open(incident_register_path_ + (string) "production_loss.csv", ios_base::out | ios_base::app);
    for (auto &item: report) {
        out_file << item.first;
        for (const auto &value: item.second) {
            out_file << "," << value;
        }
        out_file << endl;
    }
}

void Simulator::run_single() const {

    for (int i = 0; i < simulations_; ++i) {
        auto progress = ProductionManager(simulation_duration_, structure_, failures_);
        progress();
    }
}

void Simulator::prepareOutputFiles() {
    fstream out_file;
    remove(incident_register_path_);
    out_file.open(incident_register_path_, ios_base::out);
    out_file << "event,failure_id,component_id,name,description,tag,scope,capex,opex,investigation_days,procure_days,repair_days,day,simulation" << endl;
}
