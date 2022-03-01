//
// Created by Paul.Nel on 24/02/2022.
//

#include <numeric>
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
            3, "child2", duration_, 1,vector<shared_ptr<FailureMode>>(),0,1);

};

TEST_F(TestComponent, ExceptionWhenDurationLessThanZero){
    shared_ptr<Component> child3 = make_shared<Component>(
            1, "child3", duration_, 1,vector<shared_ptr<FailureMode>>(),0,1);

    ASSERT_THROW(parent_->addChild(child3), std::invalid_argument);
}


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

TEST_F(TestComponent, getCapacityReturnsCorrectCapacityIfActiveCapacityIsSet) {
    shared_ptr<Component> child3 = make_shared<Component>(
            4, "child3", duration_, 1,vector<shared_ptr<FailureMode>>(),100,1);
    shared_ptr<Component> child4 = make_shared<Component>(
            5, "child4", duration_, 1,vector<shared_ptr<FailureMode>>(),0,1);
    parent_->addChild(child3);
    child3->addChild(child4);

    auto result = child3->getCapacity();

    ASSERT_EQ(result, 100);

}

TEST_F(TestComponent, getCapacityReturnsCorrectCapacityIfActiveCapacityIsNotSet) {
    shared_ptr<Component> child3 = make_shared<Component>(
            4, "child3", duration_, 1,vector<shared_ptr<FailureMode>>(),0,1);
    shared_ptr<Component> child4 = make_shared<Component>(
            5, "child4", duration_, 1,vector<shared_ptr<FailureMode>>(),100,1);
    shared_ptr<Component> child5 = make_shared<Component>(
            6, "child5", duration_, 1,vector<shared_ptr<FailureMode>>(),100,1);
    parent_->addChild(child3);
    child3->addChild(child4);
    child3->addChild(child5);

    auto result = child3->getCapacity();

    ASSERT_EQ(result, 200);
}
TEST_F(TestComponent, scheduleCapacityLossUpdatesComponentLossCorrectly) {
    shared_ptr<Component> child3 = make_shared<Component>(
            4, "child3", duration_, 1,vector<shared_ptr<FailureMode>>(),0,1);
    shared_ptr<Component> child4 = make_shared<Component>(
            5, "child4", duration_, 1,vector<shared_ptr<FailureMode>>(),101,1);

    parent_->addChild(child3);
    child3->addChild(child4);

    child3->scheduleCapacityLoss(10,20);
    auto loss = child3->getCapacityLoss();

    double result = accumulate(loss.begin(), loss.end(), 0.);

    ASSERT_EQ(result, 2020);
}

TEST_F(TestComponent, scheduleCapacityLossUpdatesChildComponentLossCorrectlyWhenParentFailsAfter) {
    shared_ptr<Component> child3 = make_shared<Component>(
            4, "child3", duration_, 1,vector<shared_ptr<FailureMode>>(),0,1);
    shared_ptr<Component> child4 = make_shared<Component>(
            5, "child4", duration_, 1,vector<shared_ptr<FailureMode>>(),101,1);

    parent_->addChild(child3);
    child3->addChild(child4);

    child4->scheduleCapacityLoss(10,20);
    child3->scheduleCapacityLoss(15,25);
    auto loss1 = child4->getCapacityLoss();
    auto loss2 = child3->getCapacityLoss();

    double result1 = accumulate(loss1.begin(), loss1.end(), 0.);
    double result2 = accumulate(loss2.begin(), loss2.end(), 0.);
    double result3 = result1 + result2;

    ASSERT_EQ(loss1[9], 0);
    ASSERT_EQ(loss1[10], 101);
    ASSERT_EQ(loss2[39], 101);
    ASSERT_EQ(loss2[40], 0);
    ASSERT_EQ(result1, 505);
    ASSERT_EQ(result2, 2525);
    ASSERT_EQ(result3, 30*101);
}