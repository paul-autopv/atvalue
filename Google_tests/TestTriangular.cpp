//
// Created by Paul on 2021/12/30.
//
#include <cmath>
#include "gtest/gtest.h"
#include "../probabilities/TriangularProbability.h"

class TestTriangular : public ::testing::Test{

};

TEST_F(TestTriangular, ExceptionWhenShouldFailLargerWillFail){
    ASSERT_THROW(auto triangular = TriangularProbability(1, 2, 1), std::invalid_argument);
}

TEST_F(TestTriangular, ExceptionWhenInstalledLargerShouldFail){
    ASSERT_THROW(auto triangular = TriangularProbability(4, 2, 2), std::invalid_argument);
}

TEST_F(TestTriangular, ExceptionWhenInstalledLargerWillFail){
    ASSERT_THROW(auto triangular = TriangularProbability(3, 1, 1), std::invalid_argument);
}

TEST_F(TestTriangular, NoExceptionWhenInstalledLessThanShouldLessThanWill){
    ASSERT_NO_THROW(auto triangular = TriangularProbability(1, 2, 3));
}

TEST_F(TestTriangular, DayLessThanInstalledReturnZero){
    auto triangular = TriangularProbability(-100, 1, 1);

    auto probability = triangular.getProbability(-101);

    EXPECT_EQ(probability, 0);
}

TEST_F(TestTriangular, DayMoreThanWillReturnOne){
    auto triangular = TriangularProbability(1, 2, 3);

    auto probability = triangular.getProbability(4);

    EXPECT_EQ(probability, 1);
}

TEST_F(TestTriangular, DayLessThanShouldReturnCorrectValue){
    auto triangular = TriangularProbability(-10, 80, 110);

    auto probability = triangular.getProbability(55);

    EXPECT_EQ(std::floor(probability*10'000), 5416);
}

TEST_F(TestTriangular, DayMoreThanShouldReturnCorrectValue){
    auto triangular = TriangularProbability(-10, 80, 110);

    auto probability = triangular.getProbability(95);

    EXPECT_EQ(std::floor(probability*10'000), 8750);
}

TEST_F(TestTriangular, DayEqualToShouldReturnCorrectValue){
    auto triangular = TriangularProbability(-10, 80, 110);

    auto probability = triangular.getProbability(80);

    EXPECT_EQ(std::floor(probability*10'000), 7500);
}

TEST_F(TestTriangular, DayEqualtoInstalledReturnero){
    auto triangular = TriangularProbability(-10, 80, 110);

    auto probability = triangular.getProbability(-10);

    EXPECT_EQ(probability, 0);
}

TEST_F(TestTriangular, DayEqualToWillReturnOne){
    auto triangular = TriangularProbability(-10, 80, 110);

    auto probability = triangular.getProbability(110);

    EXPECT_EQ(probability, 1);
}

TEST_F(TestTriangular, DayEqualToAllReturnOne){
    auto triangular = TriangularProbability(1, 1, 1);

    auto probability = triangular.getProbability(1);

    EXPECT_EQ(probability, 1);
}

TEST_F(TestTriangular, UniqueValuesReturnCorrectValue){
    auto triangular = TriangularProbability(-15123, 730, 1095);

    auto probability = triangular.getProbability(1);

    EXPECT_EQ((int)(probability*100'000), 93254);
}

TEST_F(TestTriangular, setParamatersCorrectlyUpdatesParameters){
    auto triangular = TriangularProbability(0, 100, 200);

    auto probability1_pre = triangular.getProbability(0);
    auto probability2_pre = triangular.getProbability(100);
    auto probability3_pre = triangular.getProbability(200);

    triangular.resetProbability(300);

    auto probability0_post = triangular.getProbability(200);
    auto probability1_post = triangular.getProbability(300);
    auto probability2_post = triangular.getProbability(400);
    auto probability3_post = triangular.getProbability(500);

    EXPECT_EQ(probability1_pre, 0);
    EXPECT_EQ(probability2_pre, 0.5);
    EXPECT_EQ(probability3_pre, 1);
    EXPECT_EQ(probability0_post, 0);
    EXPECT_EQ(probability1_post, 0);
    EXPECT_EQ(probability2_post, 0.5);
    EXPECT_EQ(probability3_post, 1);
}