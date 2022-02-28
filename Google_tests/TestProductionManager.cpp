//
// Created by Paul.Nel on 25/02/2022.
//

#include "gtest/gtest.h"
#include "../models/Facility.h"
#include "../controllers/ProductionManager.h"

using InputMap = std::map<int, std::vector<std::string>>;

class TestProductionManager : public ::testing::Test{
protected:
    void SetUp() override {
        failures_ = {
                {1, {"1", "2", "Component Failure", "Component Failure Description", "tag_name", "all", "0", "0", "0", "0", "0", "triangular", "1", "2"}},
                {2, {"2", "2", "Component Failure", "Component Failure Description", "tag_name", "all", "0", "0", "0", "0", "0", "triangular", "1", "2"}},
                {3, {"3", "2", "Component Failure", "Component Failure Description", "tag_name", "all", "0", "0", "0", "0", "0", "triangular", "1", "2"}},
        };
        structure_ = {
                {1, {"1", "0", "Facility", "100", "345"}},
                {2, {"2", "1", "Component 1", "100", "3000"}},
                {3, {"3", "1", "Component 2", "50", "234"}},
                {4, {"4", "2", "Generator 1", "100", "445"}}
        };
        facility_.buildFacility(structure_, failures_);
    }

    class ProductionManagerTester : public ProductionManager{
    public:
        ProductionManagerTester(const int &duration, const InputMap &structure, const InputMap &failures) :
            ProductionManager(duration, structure, failures){};
    };

    InputMap failures_;
    InputMap structure_;
    Facility facility_ = Facility();
};

TEST_F(TestProductionManager, getShuffledFailureModesReturnsRandomListWithSameLength){
    auto manager = ProductionManagerTester(100, structure_, failures_);

    auto result = manager.hasOccurredFailure(3, 1, 0);

    EXPECT_TRUE(result);
}