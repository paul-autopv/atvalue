//
// Created by Paul on 2022/01/01.
//

#include "gtest/gtest.h"
#include "../models/Facility.h"

class FacilityTest : public ::testing::Test{

};


TEST_F(FacilityTest, addUnitAssignCorrectParentIfParentExist){
    auto new_unit_id = 234;
    auto facility = make_unique<Facility>();
    facility->addRoot(new Unit(0, "Root"));
    facility->addUnit(new_unit_id, new Unit(new_unit_id, "Test"), 0);

    auto result = facility->getParentIdOfUnit(new_unit_id);

    ASSERT_EQ(result, 0);
}