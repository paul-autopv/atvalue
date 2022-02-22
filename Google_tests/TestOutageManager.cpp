//
// Created by Paul on 2/22/22.
//

#include "gtest/gtest.h"
#include "../models/OutageManager.h"

class TestOutageManager : public ::testing::Test{
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

TEST_F(TestOutageManager, ScheduleAddsOutageCorrectlyToOutageList){
    auto manager = OutageManager();
    manager.scheduleOutage(schedule_, type_, cost_, 1);
    manager.scheduleOutage(schedule_, type_, cost_, 2);
    manager.scheduleOutage(schedule_, type_, cost_, 3);

    auto size = manager.getAllOutages().size();
    double total_cost {0};
    for (auto & outage : manager.getAllOutages()) {
        total_cost += outage.total_cost();
    }

    EXPECT_EQ(size, 3);
    EXPECT_EQ(total_cost, 33000);
}
