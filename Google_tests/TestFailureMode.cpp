//
// Created by Paul.Nel on 17/02/2022.
//

#include "gtest/gtest.h"
#include "../probabilities/WeibullProbability.h"
#include "../models/FailureMode.h"

class TestFailureMode : public ::testing::Test{

};

TEST_F(TestFailureMode, CopyConstructorCopiesCorrectly){
    auto mode = FailureMode(1, 1, "test", "test", "tag", make_unique<WeibullProbability>(1,1));
    auto copied_mode = mode;

    EXPECT_EQ(copied_mode.getId(), mode.getId());
    EXPECT_EQ(copied_mode.getUnitId(), mode.getUnitId());
    EXPECT_EQ(copied_mode.getUnitId(), mode.getUnitId());
    EXPECT_EQ(copied_mode.hasOccurred(0.7, 5), mode.hasOccurred(0.7, 5));
}