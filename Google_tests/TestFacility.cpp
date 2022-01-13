//
// Created by Paul on 2022/01/01.
//

#include "gtest/gtest.h"
#include "../models/Facility.h"

class FacilityTest : public ::testing::Test{

};

TEST_F(FacilityTest, addUnitsCreateCorrectChildrenCount){
    auto facility = make_unique<Facility>();
    facility->addRoot(make_unique<Unit>(0, "Root"));
    facility->addUnit(make_unique<Unit>(1, "Test"), 0);
    facility->addUnit(make_unique<Unit>(2, "Test"), 0);
    facility->addUnit(make_unique<Unit>(3, "Test"), 1);

    auto root_result = facility->getChildrenCountForUnit(0);
    auto unit1_result = facility->getChildrenCountForUnit(1);
    auto unit2_result = facility->getChildrenCountForUnit(2);

    ASSERT_EQ(root_result, 2);
    ASSERT_EQ(unit1_result, 1);
    ASSERT_EQ(unit2_result, 0);
}

TEST_F(FacilityTest, addUnitAssignCorrectParentIfNotRoot){
    auto new_unit_id = 234;
    auto facility = make_unique<Facility>();
    facility->addRoot(make_unique<Unit>(0, "Root"));
    facility->addUnit(make_unique<Unit>(new_unit_id, "Test"), 0);

    auto result = facility->getParentIdOfUnit(new_unit_id);

    ASSERT_EQ(result, 0);
}

TEST_F(FacilityTest, addUnitThrowErrorIfParentDoesNotExist){
    auto facility = make_unique<Facility>();
    facility->addRoot(make_unique<Unit>(0, "Root"));

    ASSERT_THROW(facility->addUnit(make_unique<Unit>(123, "Test"), 1);, std::invalid_argument);
}