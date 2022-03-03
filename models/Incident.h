//
// Created by Paul on 2/28/22.
//

#include <utility>
#include <vector>

class Incident{
public:
    Incident(const int id, std::vector<std::string> event) : id {id}, event {std::move(event)} {}

    int id{};
    std::vector<std::string> event {};
};