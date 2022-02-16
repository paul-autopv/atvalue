//
// Created by Paul on 2022/01/01.
//

#include "WeibullProbability.h"

WeibullProbability::WeibullProbability(double alpha, double beta) : alpha{alpha}, beta {beta} {

}

double WeibullProbability::getProbability(int day) {
    return alpha < beta;
}
