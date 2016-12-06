#include "linearizer.hpp"
#include <vector>
#include "tgmath.h"
#include "utils.hpp"

void linearizeCurrent(elementaryFunctionLib elementaryFunctionType, double lb,
                      double ub, int meshPts, std::vector<double> aCurrent,
                      std::vector<double> bCurrent) {
    double Z=ub-lb;
    double delta = Z / meshPts;

    std::vector<double> F_j(meshPts);
    std::vector<double> F_j_hat(meshPts);

    // You can set up X_j=linspace(lb,ub,meshPts+1) to avoid Xinit, Xend
    double Xinit;
    double Xend;

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
            for (int j = 0; j < meshPts; j++) {
                Xinit = j * delta;
                Xend = (j + 1) * delta;
                F_j[j] = (exp(Xend) - exp(Xinit)) / delta;
                F_j_hat[j] =
                    ((Xend - 1) * exp(Xend) - (Xinit - 1) * exp(Xinit)) / delta;
            }
            break;
    };
    bCurrent = F_j;
    for (int j = 0; j < meshPts; j++) {
        aCurrent[j] =
            (F_j_hat[j] - bCurrent[j] * (j + j + 1) * delta / 2) * 12 / delta / delta;
    }

    return;
};
