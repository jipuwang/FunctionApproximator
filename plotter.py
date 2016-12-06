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

def string_to_floatAr(Str):
	Str_array = Str.split(',');
	Fl_array = np.zeros(len(Str_array));
	for i in range(len(Str_array)):
		Fl_array[i] = float(Str_array[i]);
	return Fl_array;

def main():
    f = open("stringlist.txt");
    lines = f.readlines();
    zeroMom = string_to_floatAr(lines[0]);
    firstMom = string_to_floatAr(lines[1]);
    #Coeff_Ar = string_to_floatAr(lines[2]);
	#Poly_Ar = string_to_floatAr(lines[3]);
	
    n = len(zeroMom)
    Tau = 10
    Midpoints = set_midpoints(Tau, n);
    dx = Midpoints[1] - Midpoints[0]
    
    X = setup_x(n, dx)
    Y = setup_y(zeroMom, firstMom, n, dx);
    
    for i in range(0, n):
        plt.plot([X[2 * i], X[2 * i + 1]], [Y[2 * i], Y[2 * i + 1]], 'b-*')
    
    
    #plt.show()
    plt.savefig("plot.pdf", format="pdf", dpi=500);
    #X1 = np.array([1.0, 2.0]);
    #X2 = np.array([3.0, 4.0]);
    #plt.plot(X1, X1, 'b');
    #plt.plot(X2, X2, 'b');
    return;

main();
