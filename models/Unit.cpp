//
// Created by Paul on 2021/12/28.
//

#include <iostream>
#include <utility>
#include "Unit.h"

Unit::Unit(unsigned int id, std::string name) : id {id}, name {std::move(name)}{
}

Unit::Unit(std::string name) : Unit {0, std::move(name)} {
};

Unit::Unit() : Unit {0, ""}{

}

std::ostream &operator<<(std::ostream &os, const Unit &unit) {
    os << "Unit id: " << unit.id << " (" << unit.name << ")";
    return os;
}

unsigned Unit::getId() const{
    return this->id;
}

std::string Unit::getName() const {
    return this->name;
}

