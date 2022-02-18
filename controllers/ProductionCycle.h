//
// Created by Paul on 2022/01/25.
//

#ifndef ATVALUE_PRODUCTIONCYCLE_H
#define ATVALUE_PRODUCTIONCYCLE_H

class  ProductionCycle{
public:
    ProductionCycle() : ProductionCycle(0) {};
    explicit ProductionCycle(int size) : size_ {size} {
        register_.resize(size_);
    };

    vector<int> operator()() {
        vector<int> temp(size_);
        for (int i = 0; i < size_; ++i) {
                temp[i] = 1;
        }
        for (int i = 0; i < size_; ++i) {
            register_[i] += temp[i];
        }
        return register_;
    }

private:
    int size_;
    vector<int> register_;
};

#endif //ATVALUE_PRODUCTIONCYCLE_H
