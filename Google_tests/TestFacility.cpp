//
// Created by Paul on 2/20/22.
//

#include "gtest/gtest.h"
#include "../models/Facility.h"

using InputMap = std::map<int, std::vector<std::string>>;

class TestFacility : public ::testing::Test{
protected:
    void SetUp() override {
        failures_ = {
            {1, {"1", "2", "Unit Failure", "Unit Failure Description", "tag_name", "weibull", "200", "3000"}},
            {2, {"2", "2", "Unit Failure", "Unit Failure Description", "tag_name", "weibull", "200", "45"}},
            {3, {"3", "2", "Unit Failure", "Unit Failure Description", "tag_name", "weibull", "1000", "2345"}},
        };
        structure_ = {
            {1, {"1", "0", "Facility", "100", "345"}},
            {2, {"2", "1", "Unit 1", "100", "3000"}},
            {3, {"3", "1", "Unit 2", "50", "234"}},
            {4, {"4", "2", "Generator 1", "100", "445"}}
        };
        facility_.buildFacility(structure_, failures_);
    }
    InputMap failures_;
    InputMap structure_;
    Facility facility_ = Facility();
};

TEST_F(TestFacility, getShuffledFailureModesReturnsRandomListWithSameLength){
    auto result = facility_.getShuffledFailureModes();
    std::cout << result[0] << std::endl;

    EXPECT_EQ(result.size(), failures_.size());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}