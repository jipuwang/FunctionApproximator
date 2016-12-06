# -*- coding: utf-8 -*-
"""
Created on Sun Dec 04 11:15:47 2016

@author: Xinyan
"""

import math
import numpy as np
import random
import matplotlib.pyplot as plt

def set_midpoints(Tau, n):
    startMidpoint = (Tau - 0.0)/(n - 0.0)/2.0;
    endMidpoint = Tau - startMidpoint
    Midpoints = np.linspace(startMidpoint, endMidpoint, n)
    return Midpoints

def setup_x(n, dx):
    X = np.zeros(n * 2);
    for i in range(0, n):
        X[2 * i] = (i - 0.0) * dx;
        X[2 * i + 1] = (i + 1.0) * dx;
    return X

def setup_y(zeroMom, firstMom, n, dx):
    Y = np.zeros(n * 2);
    for i in range(0, n):
        Y[2*i] = zeroMom[i] - 0.5 * dx * firstMom[i];
        Y[2*i + 1] = zeroMom[i] + 0.5 * dx * firstMom[i];
    return Y

def main():
    zeroMom = np.array([-0.367876244402644, 
                        0.132123755597356,
                        0.632123755597356,
                        1.132123755597356,
                        1.632123755597356,
                        2.132123755597356,
                        2.632123755597356,
                        3.132123755597356,
                        3.632123755597356,
                        4.132123755597356,
                        4.632123755597356,
                        5.132123755597356,
                        5.632123755597356,
                        6.132123755597356,
                        6.632123755597356,
                        7.132123755597356,
                        7.632123755597356,
                        8.132123755597355,
                        8.632123755597355,
                        9.132123755597355]);
    firstMom = np.array([-0.617876244402644, 
                         -0.617876244402645, 
                         -0.617876244402642,
                         -0.617876244402642,
                         -0.617876244402635,
                         -0.617876244402635,
                         -0.617876244402661,
                         -0.617876244402661,
                         -0.617876244402609,
                         -0.617876244402609,
                         -0.617876244402609,
                         -0.617876244402714,
                         -0.617876244402714,
                         -0.617876244402714,
                         -0.617876244402714,
                         -0.617876244402714,
                         -0.617876244402503,
                         -0.617876244402503,
                         -0.617876244402925,
                         -0.617876244402925])/(-0.617876244402644);
    n = len(zeroMom)
    Tau = 10
    Midpoints = set_midpoints(Tau, n)
    dx = Midpoints[1] - Midpoints[0]
    
    X = setup_x(n, dx)
    Y = setup_y(zeroMom, firstMom, n, dx);
    
    for i in range(0, n):
        plt.plot([X[2 * i], X[2 * i + 1]], [Y[2 * i], Y[2 * i + 1]], 'b-*')
    
    
    plt.show()
    #X1 = np.array([1.0, 2.0]);
    #X2 = np.array([3.0, 4.0]);
    #plt.plot(X1, X1, 'b');
    #plt.plot(X2, X2, 'b');
    return;

main();
