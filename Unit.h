//
// Created by Paul on 2021/12/28.
//

#ifndef TREE_UNIT_H
#define TREE_UNIT_H


#include <string>

class Unit {
    unsigned id;
    std::string name;


public:
    friend std::ostream& operator<<(std::ostream& os, const Unit& unit);

    Unit(unsigned id, std::string name, double capacity = 0);
    explicit Unit(std::string name);
    Unit();

    unsigned getId() const;
    std::string getName() const;
};


#endif //TREE_UNIT_H
