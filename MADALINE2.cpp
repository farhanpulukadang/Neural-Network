#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>
#define e 2.7128
using namespace std;
const vector<vector<double>> x = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
const vector<double> t = { 1, 0, 0, 1 };
vector<vector<double>> v = { {0.2, 0.3, -0.1}, {0.3, 0.1, -0.1} };
vector<double> w = { 0.5, -0.3, -0.4 };
vector<double> b = { -0.3, 0.3, 0.3, -0.1 }, y;
double a = 0.5;
int ep = 1;
double sigmoid(double x) {
	return (1 / (1 + pow(e, -x)));
}
bool confirm() {
	if (y.size() == 0)
		return true;
	for (int i = 0; i != y.size(); i++) {
		if (abs(y[i] - t[i]) > 0.01) {
			return true;
		}
	}
	return false;
}
int main() {
	while (confirm()) {
		y.clear();
		for (int i = 0; i != x.size(); i++) {
			vector<double> z_in(w.size());
			for (int j = 0; j != x[0].size(); j++) {
				for (int k = 0; k != z_in.size(); k++) {
					z_in[k] += a * x[i][j] * v[j][k] + b[k] / x[0].size();
				}
			}
			for_each(z_in.begin(), z_in.end(), [](double& n) {n = sigmoid(n); });
			vector<double> dnet, d;
			double Z = 0;
			for (int j = 0; j != z_in.size(); j++) {
				Z += w[j] * z_in[j] + b[b.size() - 1]/z_in.size();
			}
			y.emplace_back(sigmoid(Z));
			double dk = (t[i] - y[i]) * y[i] * (1 - y[i]);
			b[b.size() - 1] += a * dk;
			for (int j = 0; j != w.size(); j++) {
				w[j] += a * dk * z_in[j];
				dnet.emplace_back(dk * w[j]);
			}
			for (int j = 0; j != dnet.size(); j++) {
				d.emplace_back(dnet[j] * z_in[j] * (1 - z_in[j]));
				for (int k = 0; k != x[0].size(); k++) {
					v[k][j] += a * d[j] * x[i][k];
				}
				b[j] += a * d[j];
			}
		}
		cout << ep << endl;
		for (const auto i : y) {
			cout << i << " ";
		}
		cout << endl;
		ep++;
	}
	return 0;
}