#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Data.h"
using namespace std;
vvd x = {Jakarta, Kuala_Lumpur, Abu_Dhabi, Muscat, Berlin, Zurich, Vladivostok, Beijing, Rainier, Nord };
const vi c = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
const vector<string> climate = {"Tropical", "Desert", "Temperate", "Continental", "Tundra"};
vvd w = {Singapore, Khartoum, Paris, Moscow, Everest};
unsigned ep = 100;
double a = 0.5, maxt = 0, mint = 0;
int main() {
	vvd all = {Jakarta, Kuala_Lumpur, Abu_Dhabi, Muscat, Berlin, Zurich, Vladivostok,
		Beijing, Rainier, Nord, Singapore, Khartoum, Paris, Moscow, Everest, Tokyo};
	for (auto i : all) {
		if (*max_element(i.begin(), i.end()) > maxt)
			maxt = *max_element(i.begin(), i.end());
		if (*min_element(i.begin(), i.end()) < mint)
			mint = *min_element(i.begin(), i.end());
	}
	for_each(x.begin(), x.end(), [&](vd& inp) {
		for_each(inp.begin(), inp.end(), [&](double& in) {in += abs(mint); in = in / (abs(mint) + maxt);});
	});
	for_each(w.begin(), w.end(), [&](vd& inp) {
		for_each(inp.begin(), inp.end(), [&](double& in) {in += abs(mint); in = in / (abs(mint) + maxt);});
	});
	for_each(Tokyo.begin(), Tokyo.end(), [&](double& in) {in += abs(mint); in = in / (abs(mint) + maxt);});
	while (ep--) {
		for (int i = 0; i != x.size(); i++) {
			vd D;
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
		a *= 0.9;
	}
	vd D;
	for (auto i : w) {
		double Dtotal = 0;
		for (int k = 0; k != x[0].size(); k++) {
			Dtotal += sqrt(pow(Tokyo[k] - i[k], 2));
		}
		D.emplace_back(Dtotal);
	}
	cout << "Predicted climate group: " << endl;
	int Dmin = distance(D.begin(), min_element(D.begin(), D.end()));
	cout << climate[Dmin];
	return 0;
}