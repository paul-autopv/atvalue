//
// Created by paul on 2021-12-18.
//

#ifndef CSVREADER_H
#define CSVREADER_H


#include <vector>
#include <string>
#include <map>
#include <unordered_map>

using InputMap = std::map<int, std::vector<std::string>>;


class CsvReader {
public:
    /**
     * Read unit structure CSV file.  First coloumn is unique id.  Must be UTF-8 encoded.
     * @param path Path to CSV
     * @return map of type <int unique_id, std::string> full comma delimited row including unit_id
     */
    static InputMap readCsv(const std::string& path, bool has_header = false);

private:
    static std::string fileToString(const std::string& path);

    static void discardLine(std::istringstream &file_entry, std::string &record);
};


#endif //ATVALUE_CPP_CSVREADER_H
