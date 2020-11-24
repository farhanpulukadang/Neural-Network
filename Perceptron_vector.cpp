//Farhan Umarnadi Pulukadang 13118209
#include <iostream>
#include <vector>
using namespace std;
const vector<vector<int>> X = {
						{1, -1, -1, -1, 1, -1, -1, -1, 1, -1, -1, -1, 1, 1, 1, -1},
						{1, -1, 1, -1, 1, 1, 1, -1, 1, -1, 1, -1, -1, -1, -1, -1},
						{1, -1, 1, -1, 1, -1, -1, -1, 1, -1, -1, 1, 1, 1, 1, -1},
						{1, -1, 1, -1, 1, 1, 1, -1, 1, -1, 1, -1, -1, -1, 1, 1}
};
vector<int> T = { 1, -1, 1, -1 }, YF;
vector<float> W(16, 0.0);
float A = 0.5, B = 0;
int epoch = 0;
int main() {
	while (T != YF) {
		YF.clear();
		for (int i = 0; i != X.size(); i++) {
			float Y = 0;
			for (int j = 0; j != X[0].size(); j++) {
				Y = Y + X[i][j] * W[j];
				W[j] = W[j] + A * X[i][j] * T[i];
			}
			Y += B;
			B = B + A * T[i];
			if (Y == 0)
				YF.emplace_back(0);
			if (Y > 0)
				YF.emplace_back(1);
			if (Y < 0)
				YF.emplace_back(-1);
		}
		printf("Iterasi ke: %i\n", epoch+1);
		for (const auto i : YF) {
			printf("%i\n", i);
		}
		epoch++;
	}
	return 0;
}
