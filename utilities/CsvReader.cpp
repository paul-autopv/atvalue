//
// Created by paul on 2021-12-18.
//
#include <fstream>
#include <iostream>
#include <sstream>

#include "CsvReader.h"

using std::ifstream;
using std::string;
using std::cout; using std::cerr; using std::endl;
using std::istringstream; using std::ostringstream;


std::string CsvReader::fileToString(const string &path)  {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}


std::map<unsigned, std::vector<string>> CsvReader::readCsv(const std::string& path, bool has_header) {

    string file_contents;
    std::map<unsigned, std::vector<string>> csv_contents;
    char delimiter = ',';

    file_contents = fileToString(path);

    istringstream sstream(file_contents);
    std::vector<string> items;
    string record;

    int counter = 0;
    if (has_header)
        std::getline(sstream, record);
    while (std::getline(sstream, record)) {
        istringstream line(record);
        while (std::getline(line, record, delimiter)) {
            items.push_back(record);
        }

        csv_contents[counter] = items;
        items.clear();
        counter += 1;
    }
    return csv_contents;
}
