//
// Created by Paul on 2021/12/28.
//

#ifndef TREE_UNIT_H
#define TREE_UNIT_H


#include <string>

using namespace std;

class Unit {
    unsigned id_;
    string name_;
    weak_ptr<Unit> parent_;
//    vector<shared_ptr<Unit>> children;


public:
    friend ostream& operator<<(ostream& os, const Unit& unit);

    Unit(unsigned id, string name);
    explicit Unit(string name);
    Unit();

    void addChild();
    unsigned getId() const;
    string getName() const;
};


#endif //TREE_UNIT_H
