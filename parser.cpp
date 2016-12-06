#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "parser.hpp"
#include "linearizer.hpp"

using namespace std;

string print_term(const int &index) {
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
}

void parser(string str, vector<int> &terms, vector<double> &coeff) {
    string func = str.substr(5);

    while (func.size() != 0) {
        double pos = 0;
        double sign = 1;
        if (func[0] == '-') {
            sign = -1;
            func = func.substr(1);
        } else if (func[0] == '+') {
            func = func.substr(1);
        }

        // get coefficient
        if (isdigit(func[0])) {
            size_t pos_t;
            double cof = stod(func, &pos_t);
            pos = double(pos_t);
            coeff.push_back(cof * sign);

        } else {
            coeff.push_back(1.0);
        }
        func = func.substr(pos);
        if (func.size() != 0 && func[0] == '*') {
            func = func.substr(1);  // remove *
        }
        // get number
        if ((func.size() == 0) || (func[0] == '-') || (func[0] == '+')) {
            // it was only a constant
            terms.push_back(0);
        } else {
            // get polynomial after the constant
            if (func[0] == 'x') {
                if ((func.size() == 1) || (func[1] == '-') ||
                    (func[1] == '+')) {
                    terms.push_back(1);
                } else {
                    terms.push_back(int(func[2] - '0'));
                }
            } else if (func[0] == 'S') {
                terms.push_back(5);
            } else if (func[0] == 'C') {
                terms.push_back(6);
            } else if (func[0] == 'T') {
                terms.push_back(7);
            } else if (func[0] == 'L') {
                if (func[1] == 'n') {
                    terms.push_back(8);
                } else {
                    terms.push_back(9);
                }
            } else if (func[0] == 'E') {
                terms.push_back(10);
            } else {
                cout << "wrong input" << endl;
            }
        }
        size_t new_start = func.size();
        if (func.find_first_of("+") < new_start) {
            new_start = func.find_first_of("+");
        }

        if (func.find_first_of("-") < new_start) {
            new_start = func.find_first_of("-");
        }

        func = func.substr(int(new_start));
    }
    return;
}

vector<double> Range_vec(const string &range)
{
	vector<double> range_vec;
	size_t pos = range.find("=");
	string useful = range.substr(pos + 1);
	//cout << useful << endl;
	double lower_bound = stod(useful, &pos);
	//cout << lower_bound << endl;
	double upper_bound = stod(useful.substr(pos + 1));
	//cout << upper_bound << endl;
	range_vec.push_back(lower_bound);
	range_vec.push_back(upper_bound);
	return range_vec;
}

int get_Mesh(const string &mesh)
{
	size_t pos = mesh.find("=");
	return stod(mesh.substr(pos + 1));
}
