//
// Created by paul on 2021-12-18.
//
#include <fstream>
#include <iostream>
#include <sstream>

#include "CsvReader.h"

using std::ifstream;
using std::string;
using std::map;
using std::cout; using std::cerr; using std::endl;
using std::istringstream; using std::ostringstream;


map<unsigned, std::vector<string>> CsvReader::readCsv(const string& path, bool has_header) {

    string file_contents;
    std::map<unsigned, std::vector<string>> csv_contents;
    char delimiter = ',';

    istringstream file_entry {fileToString(path)};
    std::vector<string> items;
    string record;

    int counter = 0;
    if (has_header)
        discardLine(file_entry, record);

    while (std::getline(file_entry, record)) {
        string unit;
        istringstream line(record);
        while (std::getline(line, unit, delimiter)) {
            items.push_back(unit);
        }

        csv_contents[counter] = items;
        items.clear();
        counter ++;
    }
    return csv_contents;
}

string CsvReader::fileToString(const string &path)  {
    auto ss = ostringstream{};
    ifstream input_file {path};
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '" << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

void CsvReader::discardLine(istringstream &file_entry, string &record) { std::getline(file_entry, record); }
