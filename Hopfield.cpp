//Farhan Umarnadi Pulukadang 13118209
//Hopfield
#include <iostream>
#include <vector>
#include <algorithm>
#include "Data_Hopfield.h"
using namespace std;
vvi x = {Luxembourg, France, Indonesia, Italy, Kenya, Congo, Venezuela}, y = {AAA, AA, BBB, BBB, B, CCC, D}, W;// 
vi res(y[0].size()), sn = {Lebanon};
vector<string> name = {"AAA", "AA", "BBB", "BBB", "B", "CCC", "D"};
vvvi w(x.size(), vvi(y[0].size(), vi(x[0].size(), 0)));
int biner(int& y) {
	if (y > 0)
		y = 1;
	else
		y = -1;
	return y;
}
int main() {
	for (int I = 0; I != x.size(); I++) {
		for (int i = 0; i != y[0].size(); i++) {
			for (int j = 0; j != x[0].size(); j++) {
				w[I][i][j] = y[I][i] * x[I][j];
			}
		}
	}
	for_each(w.begin() + 1, w.end(), [&](vvi& w_i) {
		for (unsigned i = 0; i != w_i.size(); i++) {
			for (unsigned j = 0; j != w_i[0].size(); j++) {
				w[0][i][j] += w_i[i][j];
			}
		}
	});
	W = w[0];
	for (unsigned i = 0; i != W.size(); i++) {
		int t = 0;
		for (unsigned j = 0; j != sn.size(); j++) {
			t += W[i][j] * sn[j];
		}
		res[i] = biner(t);
	}
	cout << "Predicted credit ratings: " << endl;
	for (int i = 0; i != name.size(); i++) {
		if (y[i] == res) {
			cout << name[i] << endl;
			break;
		}
	}
	return 0;
}