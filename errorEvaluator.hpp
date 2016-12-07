#pragma once

#include <vector>
// This function error evalation routine.
void errorEvaluate(std::vector<elementaryFucntionLib> terms,
                   std::vector<double> coeff, std::vector<double> aAll,
                   std::vector<double> bAll, std::vector<double> &error);
