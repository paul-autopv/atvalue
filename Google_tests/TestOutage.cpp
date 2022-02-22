//
// Created by Paul on 2/22/22.
//

#include "gtest/gtest.h"
#include "../models/Outage.h"

class TestOutage : public ::testing::Test{
protected:
    void SetUp() override {
        cost_ = OutageCost(10000, 1000);
        schedule_ = OutageSchedule(23, 5);
        type_ = OutageType::procurement;
    }

    OutageCost cost_;
    OutageSchedule schedule_;
    OutageType type_;
};

TEST_F(TestOutage, OutageDurationreturnsCorrectValue){
    auto outage = Outage(1, 1, type_, schedule_, cost_);

    auto duration = outage.duration();

    EXPECT_EQ(duration, 5);
}