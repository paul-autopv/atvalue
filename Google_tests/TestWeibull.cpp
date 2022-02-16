//
// Created by Paul on 2021/12/30.
//

#include "gtest/gtest.h"
#include "../probabilities/WeibullProbability.h"

class TestWeibull : public ::testing::Test{

};

TEST_F(TestWeibull, DayEqualToBetaReturnCorrectValue){
    WeibullProbability weibull = WeibullProbability(1,1);

    auto probability = weibull.getProbability(1);

    EXPECT_EQ(std::floor(probability*10'000), 6321);
}

TEST_F(TestWeibull, DayLessThanZeroReturnZero){
    WeibullProbability weibull = WeibullProbability(1,1);

    auto probability = weibull.getProbability(-1);

    EXPECT_EQ(probability, 0);
}

TEST_F(TestWeibull, ReturnCorrectValue){
    WeibullProbability weibull = WeibullProbability(2,3);

    auto probability = weibull.getProbability(4);

    EXPECT_EQ(std::floor(probability*10'000), 8309);
}