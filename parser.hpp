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
using namespace std;

string print_term(const int &index);
void parser(string str, vector<int> &terms, vector<double> &coeff);
vector<double> Range_vec(const string &range);
int get_Mesh(const string &mesh);
