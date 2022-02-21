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

TEST_F(TestTriangular, UniqueDayReturnCorrectValue){
    auto triangular = TriangularProbability(-15123, 730, 1095);

    auto probability = triangular.getProbability(1);

    EXPECT_EQ((int)(probability*100'000), 93254);
}

