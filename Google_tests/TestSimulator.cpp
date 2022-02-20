//
// Created by Paul.Nel on 17/02/2022.
//

#include "gtest/gtest.h"
#include "../controllers/Simulator.h"

class TestSimulator : public ::testing::Test{

};

TEST_F(TestSimulator, ExceptionWhenDurationLessThanZero){
    ASSERT_THROW(auto sim = Simulator(1, -1, InputMap(), InputMap()), std::invalid_argument);
}

TEST_F(TestSimulator, ExceptionWhenSimulationsLessThanZero){
    ASSERT_THROW(auto sim = Simulator(-1, 1, InputMap(), InputMap()), std::invalid_argument);
}