//
// Created by Paul on 2022/01/17.
//
#include <algorithm>
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

    ProductionRegister production_loss_register;
    ProductionRegister availability_register;
    for (auto future = 0; future < simulations_; ++future) {
        auto report = futures[future].get();
        cout << "Writing register for simulation " << future << endl;
        auto incidents = report.getIncidents();
        fileIncidents(incidents);
        auto production_loss = report.getProductionLoss();
        auto availabilty = report.getAvailability();
        production_loss_register = accumulateProductionLoss(production_loss, production_loss_register);
        availability_register = accumulateProductionLoss(availabilty, availability_register);
    }
    production_loss_register = normaliseProductionRegister(production_loss_register);
    availability_register = normaliseProductionRegister(availability_register);
    fileRegister(production_loss_register, "production_loss");
    fileRegister(availability_register, "availability");
}

ProductionRegister Simulator::normaliseProductionRegister(ProductionRegister production_register) const {
    if (simulations_ > 0) {
        for (auto &entry: production_register) {
            std::transform(entry.second.begin(), entry.second.end(), entry.second.begin(),
                           [this](double value) -> double { return value / simulations_; }
            );
        }
    }
    return production_register;
}


void Simulator::fileIncidents(vector<Incident> &report) {
    fstream out_file;

    out_file.open(incident_register_path_ + (string)"incidents.csv", ios_base::out | ios_base::app);
    int entry {1};
    for (auto &item: report) {
        out_file << entry;
        for (const auto& value: item.event) {
            out_file << "," << value;
        }
        out_file << endl;
        ++entry;
    }
    out_file.close();
}

void Simulator::fileRegister(ProductionRegister &report, const string &name) const {
    fstream out_file;

    out_file.open(incident_register_path_ + name + (string) ".csv", ios_base::out | ios_base::app);
    auto header = writeProductionLossReportHeader(report, out_file);

    for (int day = 0; day < simulation_duration_; ++day) {
        out_file << (day + 1) << ",";
        for (const auto &component_id: header) {
            out_file << report.at(component_id)[day] << ",";
        }
        out_file << endl;
    }
    out_file.close();
}

vector<int> Simulator::writeProductionLossReportHeader(const ProductionRegister &report, fstream &out_file) const {
    vector<int> header;
    auto start = report.begin();
    auto component_id = start->first;
    header.push_back(component_id);
    out_file << "day," << component_id;
    advance(start,1);
    for (auto it = start; it != report.end(); ++it){
        component_id = it->first;
        header.push_back(component_id);
        out_file << "," << component_id;
    }
    out_file << endl;
    return header;
}

ProductionRegister Simulator::accumulateProductionLoss(ProductionRegister &report, const ProductionRegister &productionLoss) const {

    auto loss = productionLoss;
    for (auto &entry : report){
        if (loss.find(entry.first) == loss.end()){
            loss.emplace(entry);
        }
        else {
            for (int i = 0; i < entry.second.size(); ++i) {
                loss.at(entry.first)[i] += report.at(entry.first)[i];
            }
        }
    }

    return loss;
}
void Simulator::run_single() const {

    for (int i = 0; i < simulations_; ++i) {
        auto progress = ProductionManager(simulation_duration_, structure_, failures_);
        progress();
    }
}

void Simulator::prepareOutputFiles() {
    prepareOutputFile(
            (string)incident_register_path_ + "incidents.csv",
            "event,failure_id,component_id,name,description,tag,scope,capex,opex,investigation_days,procure_days,repair_days,day,simulation"
            );

//    string loss_header {"component_id"};
//    for (unsigned int c = 1; c <= simulation_duration_; ++c){
//        auto coloumn_name = "," + to_string(c);
//        loss_header+=coloumn_name;
//    }
//
    prepareOutputFile(
            (string)incident_register_path_ + "production_loss.csv",
            ""
            );

    prepareOutputFile(
            (string)incident_register_path_ + "availability.csv",
            ""
            );
}

void Simulator::prepareOutputFile(const string& name, const string& header){
    fstream file;
    remove(&name[0]);
    file.open(name, ios_base::out | ios_base::app);
    if (!header.empty())
        file << header << endl;
    file.close();
}
