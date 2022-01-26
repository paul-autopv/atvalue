//
// Created by Paul on 2022/01/25.
//

#ifndef TREE_REGISTER_H
#define TREE_REGISTER_H

#include <iostream>
#include <memory>

class  Register{
public:
    Register() : size_ {0} {};
    explicit Register(int size) : size_ {size} {
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

#endif //TREE_REGISTER_H
