//
// Created by Paul.Nel on 24/02/2022.
//

#include "gtest/gtest.h"
#include "../models/Component.h"

class TestComponent : public ::testing::Test{
protected:
    void SetUp() override {
        parent_.addChild(make_shared<Component>(child1_));
        child1_.addChild(make_shared<Component>(child2_));
    }

    Component parent_ = Component(1, "parent", 1,vector<shared_ptr<FailureMode>>(),0,2);;
    Component child1_ = Component(2, "child1", 1,vector<shared_ptr<FailureMode>>(),0,1);
    Component child2_ = Component(1, "child2", 1,vector<shared_ptr<FailureMode>>(),0,1);
};

TEST_F(TestComponent, ShutdownUnplannedMakesUnavailableComponentAndAllChildrenWhenCalled){

    vector<bool> availability_before = { parent_.isAvailable(), child1_.isAvailable(), child2_.isAvailable() };
    parent_.shutdown(ShutdownCode::unplanned);
    vector<bool> availability_after = { parent_.isAvailable(), child1_.isAvailable(), child2_.isAvailable() };

    EXPECT_TRUE(availability_before.at(0) && availability_before.at(1) && availability_before.at(2) );
    EXPECT_FALSE(availability_after.at(0) && availability_after.at(1) && availability_after.at(2) );
}

TEST_F(TestComponent, ShutdownPlannedMakesUnavailableComponentAndAllChildrenWhenCalled){

    vector<bool> availability_before = { parent_.isAvailable(), child1_.isAvailable(), child2_.isAvailable() };
    parent_.shutdown(ShutdownCode::planned);
    vector<bool> availability_after = { parent_.isAvailable(), child1_.isAvailable(), child2_.isAvailable() };

    EXPECT_TRUE(availability_before.at(0) && availability_before.at(1) && availability_before.at(2) );
    EXPECT_FALSE(availability_after.at(0) && availability_after.at(1) && availability_after.at(2) );
}

TEST_F(TestComponent, ShutdownConstrainedNotMakeUnavailableComponentAndAllChildrenWhenCalled){

    vector<bool> availability_before = { parent_.isAvailable(), child1_.isAvailable(), child2_.isAvailable() };
    parent_.shutdown(ShutdownCode::constrained);
    vector<bool> availability_after = { parent_.isAvailable(), child1_.isAvailable(), child2_.isAvailable() };

    EXPECT_TRUE(availability_before.at(0) && availability_before.at(1) && availability_before.at(2) );
    EXPECT_TRUE(availability_after.at(0) && availability_after.at(1) && availability_after.at(2) );
}

TEST_F(TestComponent, ShutdownUnplannedMakesNotOnlineComponentAndAllChildrenWhenCalled){

    vector<bool> availability_before = { parent_.isOnline(), child1_.isOnline(), child2_.isOnline() };
    parent_.shutdown(ShutdownCode::unplanned);
    vector<bool> availability_after = { parent_.isOnline(), child1_.isOnline(), child2_.isOnline() };

    EXPECT_TRUE(availability_before.at(0) && availability_before.at(1) && availability_before.at(2) );
    EXPECT_FALSE(availability_after.at(0) && availability_after.at(1) && availability_after.at(2) );
}

TEST_F(TestComponent, ShutdownPlannedMakesNotOnlineComponentAndAllChildrenWhenCalled){

    vector<bool> availability_before = { parent_.isOnline(), child1_.isOnline(), child2_.isOnline() };
    parent_.shutdown(ShutdownCode::planned);
    vector<bool> availability_after = { parent_.isOnline(), child1_.isOnline(), child2_.isOnline() };

    EXPECT_TRUE(availability_before.at(0) && availability_before.at(1) && availability_before.at(2) );
    EXPECT_FALSE(availability_after.at(0) && availability_after.at(1) && availability_after.at(2) );
}

TEST_F(TestComponent, ShutdownConstrainedMakesNotOnlineComponentAndAllChildrenWhenCalled){

    vector<bool> availability_before = { parent_.isOnline(), child1_.isOnline(), child2_.isOnline() };
    parent_.shutdown(ShutdownCode::constrained);
    vector<bool> availability_after = { parent_.isOnline(), child1_.isOnline(), child2_.isOnline() };

    EXPECT_TRUE(availability_before.at(0) && availability_before.at(1) && availability_before.at(2) );
    EXPECT_FALSE(availability_after.at(0) && availability_after.at(1) && availability_after.at(2) );
}