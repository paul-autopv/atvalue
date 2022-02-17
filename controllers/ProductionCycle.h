//
// Created by Paul on 2022/01/25.
//

#ifndef TREE_PRODUCTIONCYCLE_H
#define TREE_PRODUCTIONCYCLE_H

class  ProductionCycle{
public:
    ProductionCycle() : ProductionCycle(0) {};
    explicit ProductionCycle(int duration) : duration_ {duration} {
        register_.resize(duration_);
    };

    vector<int> operator()() {
        vector<int> temp(duration_);
        for (int i = 0; i < duration_; ++i) {
                temp[i] = 1;
        }
        for (int i = 0; i < duration_; ++i) {
            register_[i] += temp[i];
        }
        return register_;
    }

private:
    int duration_;
    vector<int> register_;
};

#endif //TREE_PRODUCTIONCYCLE_H
