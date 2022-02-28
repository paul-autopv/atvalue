#include <iostream>

#include "models/Facility.h"
#include "utilities/CsvReader.h"
#include "controllers/Simulator.h"

using InputMap = std::map<int, std::vector<std::string>>;

int main() {

    std::cout << "Hello, AtValue!" << std::endl;

    auto failures = CsvReader::readCsv(R"(../data/failure_modes.csv)", true);
    auto structure = CsvReader::readCsv(R"(../data/model_1.csv)", true);

    int simulations {2};
    int duration {8000};

    auto simulator = Simulator(simulations, duration, failures, structure);
    auto start = chrono::steady_clock::now();
    simulator.run();
//    simulator.run_single();
    auto end = chrono::steady_clock::now();
    chrono::duration<double> concurrent_elapsed = end - start;
    std::cout << "Concurrent elapsed time: " << concurrent_elapsed.count() << "s\n";
    std::cout << "Concurrent elapsed time: " << concurrent_elapsed.count() / simulations << "s/simulation\n";
//
//    start = chrono::steady_clock::now();
//    simulator.run_single();
//    end = chrono::steady_clock::now();
//
//    chrono::duration<double> single_elapsed = end - start;
//    std::cout << "Single elapsed time: " << single_elapsed.count() << "s\n";
//    std::cout << "Single elapsed time: " << single_elapsed.count() / simulations << "s/simulation\n";
//
//    auto ratio = 100 * (1 - concurrent_elapsed/single_elapsed);
//    std::cout << "Concurrent is " <<  ratio  << "% faster than Single." << endl;

    return 0;
}
