//
// Created by Paul on 2021/12/30.
//

#include "gtest/gtest.h"
#include "../models/Unit.h"

class UnitTest : public ::testing::Test{

};

TEST_F(UnitTest, TwoArgConstructor){
    Unit unit = Unit(23, "Test Unit");

    auto id = unit.getId();
    auto name = unit.getName();

    EXPECT_EQ(id, 23);
    EXPECT_EQ(name, "Test Unit");
}