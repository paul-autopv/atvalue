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

    OutageCost cost_ = OutageCost(0,0);
    OutageSchedule schedule_;
    OutageType type_;
};

TEST_F(TestOutage, DurationReturnsCorrectValue){
    auto outage = Outage(1, 1, type_, schedule_, cost_);

    auto result = outage.duration();

    EXPECT_EQ(result, 5);
}

TEST_F(TestOutage, DurationReturnsZeroIfInitialisedToLessThanZero){
    auto schedule = OutageSchedule(1, -1);
    auto outage = Outage(1, 1, type_, schedule, cost_);

    auto result = outage.duration();

    EXPECT_EQ(result, 0);
}

TEST_F(TestOutage, EndReturnsStartIfDurationInitialisedToLessThanZero){
    auto schedule = OutageSchedule(1, -1);
    auto outage = Outage(1, 1, type_, schedule, cost_);

    auto result = outage.end();

    EXPECT_EQ(result, 1);
}

TEST_F(TestOutage, EndReturnsCorrectValue){
    auto outage = Outage(1, 1, type_, schedule_, cost_);

    auto result = outage.end();

    EXPECT_EQ(result, 27);
}

TEST_F(TestOutage, TotalCostReturnsCorrectValue){
    auto outage = Outage(1, 1, type_, schedule_, cost_);

    auto result = outage.total_cost();

    EXPECT_EQ(result, 11000);
}

TEST_F(TestOutage, DailyCostReturnsCorrectValue){
    auto outage = Outage(1, 1, type_, schedule_, cost_);

    auto result = outage.daily_cost();

    EXPECT_EQ(result, 2200);
}

TEST_F(TestOutage, DailyCostReturnsZeroWhenDurationIsZero){
    auto schedule = OutageSchedule(1, 0);
    auto outage = Outage(1, 1, type_, schedule, cost_);

    auto result = outage.daily_cost();

    EXPECT_EQ(result, 0);
}
