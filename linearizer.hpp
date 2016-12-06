#pragma once
#include <vector>

// THis is the function used to linearize an elementary function indexed by
// elementaryFunctionType. 
// todo: change the int elementaryFunction to a enumType
void linearizeCurrent(int elementaryFunctionType, double lb, double ub, 
        int meshPts, std::vector<double> aCurrent, std::vector<double> bCurrent);

