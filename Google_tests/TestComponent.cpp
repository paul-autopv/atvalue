//
// Created by Paul.Nel on 24/02/2022.
//

#include "gtest/gtest.h"
#include "../models/Component.h"

class TestComponent : public ::testing::Test{
protected:
    void SetUp() override {
        child1_->addChild(child2_);
        parent_->addChild(child1_);
    }
    int duration_ {1000};

    shared_ptr<Component> parent_ = make_shared<Component>(
            1, "parent", duration_, 1,vector<shared_ptr<FailureMode>>(),0,2);
    shared_ptr<Component> child1_ = make_shared<Component>(
            2, "child1", duration_, 1,vector<shared_ptr<FailureMode>>(),0,1);
    shared_ptr<Component> child2_ = make_shared<Component>(
            1, "child2", duration_, 1,vector<shared_ptr<FailureMode>>(),0,1);

};

TEST_F(TestComponent, scheduleOutageCorrectlyAllocatesAvailabilityDays){

    int pre_outage_days {0};
    auto availability = child1_->getAvailability();
    for (auto day = availability.begin(); day < availability.end(); ++day){
        pre_outage_days += *day;
    };

    child1_->scheduleOutage(4, 10);

    int post_outage_days {0};
    availability = child1_->getAvailability();
    for (auto day = availability.begin(); day < availability.end(); ++day){
        post_outage_days += *day;
    };

    auto last_day_available = child1_->isAvailable(3);
    auto first_day_unavailable = child1_->isAvailable(4);
    auto last_day_unavailable = child1_->isAvailable(13);

    ASSERT_EQ(pre_outage_days, duration_);
    ASSERT_EQ(post_outage_days, duration_ - 10);
    ASSERT_TRUE(last_day_available && !first_day_unavailable && !last_day_unavailable);

}

