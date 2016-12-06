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

int main() {
    string user_input = "f(x)=-1.3*Ln[x]+5+3.5*x^2-2.6*Exp[x]-35,Range=-1.2:3.5,Mesh=100";
    
    size_t pos = user_input.find(",");
	string f = user_input.substr(0, int(pos));		//first string, function
	cout << "Function: " << f << endl;
    
    vector<int> terms;
    vector<double> coeff;
    parser(f, terms, coeff);
    for (int i = 0; i < int(terms.size()); ++i) {
        cout << coeff[i] << ' ' << terms[i] << endl;
    }
    
    string str2 = user_input.substr(int(pos) + 1);
	pos = str2.find(",");
	string range = str2.substr(0, int(pos));		//second useful string, range
	string mesh = str2.substr(int(pos) + 1);		//third useful string, mesh
	vector<double> range_vec = Range_vec(range);
	cout << "range " << range_vec[0] << ':' << range_vec[1] << endl;
	int Mesh_val = get_Mesh(mesh);
	cout << "Mesh: " << Mesh_val << endl;

    // aAll, bAll of size mesh intervals are accumulated 0th and 1st moments.
    int meshPts = 40;
    vector<double> aAll(meshPts, 0.0);
    vector<double> bAll(meshPts, 0.0);
    vector<double> aCurrent(meshPts, 0.0);
    vector<double> bCurrent(meshPts, 0.0);

    double lb = 0.0;
    double ub = 10.0;

    for (int iTerm = 0; iTerm < int(terms.size()); iTerm++) {
        linearizeCurrent(terms[iTerm], lb, ub, meshPts, aCurrent, bCurrent);
        for (int iMesh = 0; iMesh < meshPts; iMesh++) {
            aAll[iMesh] += aCurrent[iMesh] * coeff[iTerm];
            bAll[iMesh] += bCurrent[iMesh] * coeff[iTerm];
        }
    }
    return 0;
}
