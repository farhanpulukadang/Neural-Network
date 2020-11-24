//Back Propagation Neural Networks
//Farhan Umarnadi Pulukadang (13118209)
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define e 2.7128
#define vd vector<double>
#define vvd vector<vector<double>>
using namespace std;
const vvd x = {//  GDP(PPP)/capita ; life expectancy ; education index
					   /*US*/ {0.559,		0.789,		0.900},
					   /*AU*/ {0.455,		0.833,		0.939},
					   /*CH*/ {0.635,		0.834,		0.891},
					   /*DE*/ {0.475,		0.812,		0.914},
					   /*BR*/ {0.129,		0.757,		0.681},
					   /*KE*/ {0.0442,		0.633,		0.518},
					   /*NG*/ {0.04488,		0.543,		0.477},
					   /*PH*/ {0.076,		0.711,		0.637} };
const vd t = { 0.92, 0.938, 0.946, 0.939, 0.761, 0.579,  0.534, 0.712}; //HDI
const unsigned n = x[0].size(), p = 5; // Nguyen Widrow Initialization (p is hidden layer)
const double B = 0.7 * pow(p, 1/n), a = 0.4, mu = 0.5;
vvd v(n, vd(p, B * 1 / sqrt(n))), v_prev = v;
vd w = {0.5, -0.3, -0.4}, b = {-0.3, 0.3, 0.3, -0.1}, y, w_prev = w;
int ep = 1;
double sigmoid(double x) {
	return (1 / (1 + pow(e, -x)));
}
bool confirm() {
	if (y.size() == 0)
		return true;
	for (int i = 0; i != y.size(); i++) {
		if (abs(y[i] - t[i]) > 0.02) {
			return true;
		}
	}
	return false;
}
int main() {
	while (confirm()) {
		y.clear();
		for (int i = 0; i != x.size(); i++) {
			vd z_in(w.size());
			for (int j = 0; j != x[0].size(); j++) {
				for (int k = 0; k != z_in.size(); k++) {
					z_in[k] += a * x[i][j] * v[j][k] + b[k] / x[0].size();
				}
			}
			for_each(z_in.begin(), z_in.end(), [](double& n) {n = sigmoid(n); });
			vd dnet, d;
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
				if (ep > 1) {
					vd wt = w;
					w[j] += mu * (w[j] - w_prev[j]); //Momentum
					w_prev = wt;
				}
			}
			for (int j = 0; j != dnet.size(); j++) {
				d.emplace_back(dnet[j] * z_in[j] * (1 - z_in[j]));
				for (int k = 0; k != x[0].size(); k++) {
					v[k][j] += a * d[j] * x[i][k];
					if (ep > 1) {
						vvd vt = v;
						v[k][j] += mu* (v[k][j] - v_prev[k][j]); //Momentum
						v_prev = vt;
					}
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
	//Prediction result
	vd ID = { 0.129,		0.757,		0.681 };
	vd z_in(w.size());
	for (int j = 0; j != ID.size(); j++) {
		for (int k = 0; k != z_in.size(); k++) {
			z_in[k] += a * ID[j] * v[j][k] + b[k] / x[0].size();
		}
	}
	for_each(z_in.begin(), z_in.end(), [](double& n) {n = sigmoid(n); });
	double Z = 0;
	for (int j = 0; j != z_in.size(); j++) {
		Z += w[j] * z_in[j] + b[b.size() - 1] / z_in.size();
	}
	Z = sigmoid(Z);
	cout << endl;
	cout << "BR predicted HDI: ";
	cout << Z << endl;
	return 0;
}