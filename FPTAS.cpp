#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));
	
	double e = 0.01;
	
	// Generate a sample.
	int N = 20;
	double V = (rand() % 9999 + 1) / 100.0;
	vector<int> S(N);
	vector<vector<double>> v(N), w(N);
	vector<vector<int>> x(N);
	for (int i = 0; i < N; i++) {
		S[i] = 20;
		vector<double> vi(S[i]), wi(S[i]);
		vector<int> xi(S[i], 0);
		for (int j = 0; j < S[i]; j++) {
			vi[j] = (rand() % 9999 + 1) / 100.0;
			wi[j] = (rand() % 9999 + 1) / 100.0;
		}
		v[i] = vi;
		w[i] = wi;
		x[i] = xi;
	}
	
	// FPTAS
	clock_t st = clock();
	double P = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < S[i]; j++)
			if (P < v[i][j])
				P = v[i][j];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < S[i]; j++)
			v[i][j] = int(v[i][j] * N / e / P);
	vector<double> dp(N * int(N / e) + 1, 100);
	dp[0] = 0;
	vector<vector<int>> sol(N);
	for (int i = 0; i < N; i++) {
		vector<int> soli(N * int(N / e) + 1, 0);
		sol[i] = soli;
		for (int j = N * int(N / e); j >= 0; j--)
			for (int k = 0; k < S[i]; k++)
				if (j >= v[i][k] && dp[j - v[i][k]] + w[i][k] < dp[j]) {
					dp[j] = dp[j - v[i][k]] + w[i][k];
					sol[i][j] = k + 1;
				}
	}
	int opt;
	for (opt = N * int(N / e); opt >= 0; opt--)
		if (dp[opt] <= V)
			break;
	for (int i = N - 1, j = opt; i >= 0; i--)
		if (sol[i][j] > 0) {
			x[i][sol[i][j] - 1] = 1;
			j -= v[i][sol[i][j] - 1];
		}
	clock_t et = clock();
	cout << 1.0 * (et - st) / CLOCKS_PER_SEC << endl;
	return 0;
}
