//
// Created by Paul.Nel on 24/02/2022.
//

#include "gtest/gtest.h"
#include "../models/Component.h"

class TestComponent : public ::testing::Test{

};

TEST_F(TestComponent, DayMoreThanWillReturnOne){
    auto component = Component(1, "test", 1,vector<shared_ptr<FailureMode>>(),0,3);

   component.shutdown(ShutdownCode::unplanned);

    EXPECT_EQ(probability, 1);
}