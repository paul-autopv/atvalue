//
// Created by Paul on 2021/12/28.
//

#ifndef TREE_UNIT_H
#define TREE_UNIT_H


#include <string>
#include <vector>

using namespace std;

class Unit {
    unsigned id_;
    string name_;
    weak_ptr<Unit> parent_;
    vector<shared_ptr<Unit>> children_;


public:
    friend ostream& operator<<(ostream& os, const Unit& unit);

    Unit() = delete;
    Unit(unsigned id, string name);

    void setParent(const shared_ptr<Unit>&);
    void addChild(const shared_ptr<Unit>& child);
    bool isRoot() const;
    unsigned getId() const;
    string getName() const;
};


#endif //TREE_UNIT_H
