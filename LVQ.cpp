#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define vvi vector<vector<int>>
#define vvd vector<vector<double>>
#define vi vector<int>
using namespace std;
const vvi x = { {0, 0, 1, 0, 0, 1},
				{0, 0, 1, 0, 1, 0},
				{0, 1, 0, 0, 0, 1},
				{1, 0, 1, 0, 1, 1},
				{0, 0, 1, 1, 0, 0},
				{0, 1, 0, 1, 0, 0}, 
				{1, 0, 0, 1, 0, 1}, 
				{0, 1, 1, 1, 1, 1} };
const vi c = {1, 1, 1, 1, 2, 2, 2, 2};
vvd w = { {1, 0, 0, 0, 1, 0 },
		  {0, 1, 1, 1, 1, 0} };
unsigned ep = 100;
double a = 0.05;
int main() {
	while (ep--) {
		for (int i = 0; i != x.size(); i++) {
			vi D;
			for (auto j : w) {
				double Dtotal = 0;
				for (int k = 0; k != x[0].size(); k++) {
					Dtotal += sqrt(pow(x[i][k] - j[k], 2));
				}
				D.emplace_back(Dtotal);
			}
			int Dmin = distance(D.begin(), min_element(D.begin(), D.end()));
			for (int j = 0; j != w[0].size(); j++) {
				if (Dmin + 1 == c[i])
					w[Dmin][j] += a * (x[i][j] - w[Dmin][j]);
				else
					w[Dmin][j] -= a * (x[i][j] - w[Dmin][j]);
			}
		}
		a *= 0.95;
	}

	return 0;
}