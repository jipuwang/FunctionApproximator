#include "linearizer.hpp"
#include <vector>
#include "utils.hpp"

void linearizeCurrent(elementaryFunctionLib elementaryFunctionType, double lb,
                      double ub, int meshPts, std::vector<double> aCurrent,
                      std::vector<double> bCurrent) {
    switch (elementaryFunctionType) {
        case CONST:
            break;
        case POLY1:
            break;
        case POLY2:
            break;
        case POLY3:
            break;
        case POLY4:
            break;
        case SINE:
            break;
        case COSINE:
            break;
        case TANGENT:
            break;
        case LN:
            break;
        case LOG:
            break;
        case EXP:
            break;
    };
    /*  string print_term(const int &index) {
      if (index == 0) {
          return "";
      } else if (index == 1) {
          return "x";
      } else if (index == 2) {
          return "x^2";
      } else if (index == 3) {
          return "x^3";
      } else if (index == 4) {
          return "x^4";
      } else if (index == 5) {
          return "Sin(x)";
      } else if (index == 6) {
          return "Cos(x)";
      } else if (index == 7) {
          return "Tan(x)";
      } else if (index == 8) {
          return "Ln(x)";
      } else if (index == 9) {
          return "Log(x)";
      } else if (index == 10) {
          return "Exp(x)";
      }
      return "wrong";
      */
    return;
};
