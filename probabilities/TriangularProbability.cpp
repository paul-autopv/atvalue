//
// Created by Paul on 2022/01/17.
//

#include "TriangularProbability.h"

TriangularProbability::TriangularProbability(unsigned int should_fail, unsigned int will_fail)
: days_to_should_fail {should_fail}, days_to_will_fail {will_fail} {

}

double TriangularProbability::getProbability(int day) {
    return days_to_will_fail > days_to_should_fail;
}
