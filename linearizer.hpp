#pragma once
#include <vector>

#include "utils.hpp"

// THis is the function used to linearize an elementary function indexed by
// elementaryFunctionType.
// todo: change the int elementaryFunction to a enumType
void linearizeCurrent(elementaryFunctionLib elementaryFunctionType, double lb,
                      double ub, int meshPts, std::vector<double> &aCurrent,
                      std::vector<double> &bCurrent);
