#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "linearizer.hpp"
#include "parser.hpp"
#include "utils.hpp"

using namespace std;

void output_vector_to_file(vector<double> vec_write, ofstream &myfile) {
    for (auto i = 0; i < int(vec_write.size()) - 1; ++i) {
        myfile << vec_write[i] << ',';
    }
    myfile << vec_write[int(vec_write.size()) - 1] << endl;
    return;
}

int main() {
    string user_input =
        "f(x)=-1.3*Ln[x]+5+3.5*x^2-2.6*Exp[x]-35,Range=-1.2:3.5,Mesh=100";

    size_t pos = user_input.find(",");
    string f = user_input.substr(0, int(pos));  // first string, function
    cout << "Function: " << f << endl;

    vector<elementaryFunctionLib> terms;
    vector<double> coeff;
    parser(f, terms, coeff);
    for (int i = 0; i < int(terms.size()); ++i) {
        cout << coeff[i] << ' ' << terms[i] << endl;
    }

    string str2 = user_input.substr(int(pos) + 1);
    pos = str2.find(",");
    string range = str2.substr(0, int(pos));  // second useful string, range
    string mesh = str2.substr(int(pos) + 1);  // third useful string, mesh
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

    ofstream myfile;
    myfile.open("test.txt");
    myfile << user_input << endl;
    output_vector_to_file(aAll, myfile);
    output_vector_to_file(bAll, myfile);
    myfile.close();

    return 0;
}
