#include <iostream>

#include "models/Facility.h"
#include "utilities/CsvReader.h"
#include "controllers/Simulator.h"

int main() {

//    Added Jira
    std::cout << "Hello, AtValue!" << std::endl;

    auto failure_modes = CsvReader::readCsv(R"(C:\Users\paul.nel\Documents\repos\atvalue_cpp\data\failure_modes.csv)", true);
    auto station = CsvReader::readCsv(R"(C:\Users\paul.nel\Documents\repos\atvalue_cpp\data\model_1.csv)", true);

    auto facility = make_unique<Facility>();
    facility->buildFacility(station, failure_modes);

    int simulations {1000};
    int duration {8000};

    auto simulator = Simulator(simulations, move(facility), duration);
    auto start = chrono::steady_clock::now();
    simulator.run();
    auto end = chrono::steady_clock::now();
    chrono::duration<double> concurrent_elapsed = end - start;
    std::cout << "Concurrent elapsed time: " << concurrent_elapsed.count() << "s\n";
    std::cout << "Concurrent elapsed time: " << concurrent_elapsed.count() / simulations << "s/simulation\n";

    start = chrono::steady_clock::now();
    simulator.run_single();
    end = chrono::steady_clock::now();

    chrono::duration<double> single_elapsed = end - start;
    std::cout << "Single elapsed time: " << single_elapsed.count() << "s\n";
    std::cout << "Single elapsed time: " << single_elapsed.count() / simulations << "s/simulation\n";

    auto ratio = 100 * (1 - concurrent_elapsed/single_elapsed);
    std::cout << "Concurrent is " <<  ratio  << "% faster than Single." << endl;

    return 0;
}
