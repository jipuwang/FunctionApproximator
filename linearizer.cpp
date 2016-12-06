#include "linearizer.hpp"
#include <vector>
#include "tgmath.h"
#include "utils.hpp"

void linearizeCurrent(elementaryFunctionLib elementaryFunctionType, double lb,
                      double ub, int meshPts, std::vector<double> &aCurrent,
                      std::vector<double> &bCurrent) {
    double Z = ub - lb;
    double delta = Z / meshPts;

    std::vector<double> F_j(meshPts);
    std::vector<double> F_j_hat(meshPts);

    // You can set up X_j=linspace(lb,ub,meshPts+1) to avoid Xinit, Xend
    std::vector<double> X_j(meshPts + 1);
    for (int j = 0; j < meshPts + 1; j++) {
        X_j[j] = lb + j * delta;
    }

    double Xinit;
    double Xend;

    int n = 0;

    switch (elementaryFunctionType) {
        case CONST:
            n = 0;
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
                F_j[j] = (Xend - Xinit) / (n + 1) / delta;
                F_j_hat[j] = (Xend * Xend - Xinit * Xinit) / (n + 2) / delta;
            }
            break;
        case POLY1:
            n = 1;
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
                F_j[j] = (Xend * Xend - Xinit * Xinit) / (n + 1) / delta;
                F_j_hat[j] = (Xend * Xend * Xend - Xinit * Xinit * Xinit) /
                             (n + 2) / delta;
            }
            break;
        case POLY2:
            n = 2;
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
                F_j[j] = (Xend * Xend * Xend - Xinit * Xinit * Xinit) /
                         (n + 1) / delta;
                F_j_hat[j] = (Xend * Xend * Xend * Xend -
                              Xinit * Xinit * Xinit * Xinit) /
                             (n + 2) / delta;
            }
            break;
        case POLY3:
            n = 3;
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
                F_j[j] = (Xend * Xend * Xend * Xend -
                          Xinit * Xinit * Xinit * Xinit) /
                         (n + 1) / delta;
                F_j_hat[j] = (Xend * Xend * Xend * Xend * Xend -
                              Xinit * Xinit * Xinit * Xinit * Xinit) /
                             (n + 2) / delta;
            }
            break;
        case POLY4:
            n = 4;
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
                F_j[j] = (Xend * Xend * Xend * Xend * Xend -
                          Xinit * Xinit * Xinit * Xinit * Xinit) /
                         (n + 1) / delta;
                F_j_hat[j] = (Xend * Xend * Xend * Xend * Xend * Xend -
                              Xinit * Xinit * Xinit * Xinit * Xinit * Xinit) /
                             (n + 2) / delta;
            }

            break;
        case SINE:
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
                F_j[j] = (cos(Xinit) - cos(Xend)) / delta;
                F_j_hat[j] = (sin(Xend) - sin(Xinit) + (Xinit)*cos(Xinit) -
                              (Xend)*cos(Xend)) /
                             delta;
            }

            break;
        case COSINE:
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
                F_j[j] = (sin(Xend) - sin(Xinit)) / delta;
                F_j_hat[j] = (cos(Xend) - cos(Xinit) + (Xend)*sin(Xend) -
                              (Xinit)*sin(Xinit)) /
                             delta;
            }

            break;
        case TANGENT:
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
            }
            break;
        case LN:
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
                F_j[j] =
                    (Xinit - Xinit * log(Xinit) - Xend + Xend * log(Xend)) /
                    delta;
                F_j_hat[j] =
                    (0.25 * (Xinit * Xinit - 2 * Xinit * Xinit * log(Xinit) -
                             Xend * Xend + 2 * Xend * Xend * log(Xend))) /
                    delta;
            }
            break;
        case LOG:  // log10
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
                F_j[j] =
                    (Xinit - Xinit * log10(Xinit) - Xend + Xend * log10(Xend)) /
                    delta;
                F_j_hat[j] =
                    (0.25 * (Xinit * Xinit - 2 * Xinit * Xinit * log10(Xinit) -
                             Xend * Xend + 2 * Xend * Xend * log10(Xend))) /
                    delta;
            }
            break;
        case EXP:
            for (int j = 0; j < meshPts; j++) {
                Xinit = X_j[j];
                Xend = X_j[j + 1];
                F_j[j] = (exp(Xend) - exp(Xinit)) / delta;
                F_j_hat[j] =
                    ((Xend - 1) * exp(Xend) - (Xinit - 1) * exp(Xinit)) / delta;
            }
            break;
    };
    bCurrent = F_j;
    for (int j = 0; j < meshPts; j++) {
        aCurrent[j] = (F_j_hat[j] - bCurrent[j] * (j + j + 1) * delta / 2) *
                      12 / delta / delta;
    }

    return;
};
