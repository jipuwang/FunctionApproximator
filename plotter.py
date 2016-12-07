# -*- coding: utf-8 -*-
"""
Created on Sun Dec 04 11:15:47 2016

@author: Xinyan
"""

import math
import numpy as np
import random
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt

def set_midpoints(start, Tau, n):
    startMidpoint = start + (Tau - start)/(n - 0.0)/2.0;
    endMidpoint = Tau + start - startMidpoint
    Midpoints = np.linspace(startMidpoint, endMidpoint, n)
    return Midpoints

def setup_x(start, n, dx):
    X = np.zeros(n * 2);
    for i in range(0, n):
        X[2 * i] = (i - 0.0) * dx + start;
        X[2 * i + 1] = (i + 1.0) * dx + start;
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
	
def func_val(index, x):
	if(index == 0.0):
		return 1.0;
	elif(index == 1.0):
		return x;
	elif(index == 2.0):
		return x**2.0;
	elif(index == 3.0):
		return x ** 3.0;
	elif(index == 4.0):
		return x ** 4.0;
	elif(index == 5.0):
		return math.sin(x);
	elif(index == 6.0):
		return math.cos(x);
	elif(index == 7.0):
		return math.tan(x);
	elif(index == 8.0):
		return math.log(x);
	elif(index == 9.0):
		return math.log10(x);
	elif(index == 10.0):
		return math.exp(x);
	else:
		print "something wrong"
		return 0;


def analytical_plotter(Coeff_Ar, Poly_Ar, start, n, dx):
	x_array = np.zeros(n);
	y_array = np.zeros(n);
	size = len(Coeff_Ar);
	for i in range(0, n):
		y = 0;
		x = start + i * dx;
		for j in range(0, size):
			y = y + Coeff_Ar[j] * func_val(Poly_Ar[j], x);
		y_array[i] = y;
		x_array[i] = x;
	plt.plot(x_array, y_array, 'r')
	return;


def main():
    f = open("test.txt");
    lines = f.readlines();
    func_name = lines[0];
    zeroMom = string_to_floatAr(lines[1]);
    firstMom = string_to_floatAr(lines[2]);
    Coeff_Ar = string_to_floatAr(lines[3]);
    Poly_Ar = string_to_floatAr(lines[4]);
    range_vec = string_to_floatAr(lines[5]);
    
    n = len(zeroMom)
    Tau = range_vec[1]
    Midpoints = set_midpoints(range_vec[0], Tau, n);
    dx = Midpoints[1] - Midpoints[0]
    
    X = setup_x(range_vec[0], n, dx)
    Y = setup_y(zeroMom, firstMom, n, dx);
    
    for i in range(0, n):
        plt.plot([X[2 * i], X[2 * i + 1]], [Y[2 * i], Y[2 * i + 1]], 'b-*')
    
    analytical_plotter(Coeff_Ar, Poly_Ar, range_vec[0], n, dx);
    
    #plt.show()
    #add labels
    ana_label = mpl.lines.Line2D([], [], color='red', marker='*',
                          markersize=15, label='Analytical Curve');
    num_label = mpl.lines.Line2D([], [], color='blue',
                          markersize=15, label='Approximation Curve');
    plt.legend(handles=[ana_label, num_label], loc='best');
    
    plt.grid(True) #add grid
    plt.xlabel("x");
    plt.ylabel("f(x)");
    plt.title(func_name);
    plt.savefig("plot.pdf", format="pdf", dpi=500);
    #X1 = np.array([1.0, 2.0]);
    #X2 = np.array([3.0, 4.0]);
    #plt.plot(X1, X1, 'b');
    #plt.plot(X2, X2, 'b');
    return;

main();
