#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));
	
	double e = 0.01;
	
	// Generate a sample.
//	int N = rand() % 100 + 1;
	int N = 20;  // for testing
	double V = (rand() % 9999 + 1) / 100.0;
	vector<int> S(N);
	vector<vector<double>> v(N), w(N);
	vector<vector<int>> x(N);
	for (int i = 0; i < N; i++) {
//		S[i] = rand() % 100 + 1;
		S[i] = 20;  // for testing
		vector<double> vi(S[i]), wi(S[i]);
		vector<int> xi(S[i], 0);
		v[i] = vi;
		w[i] = wi;
		x[i] = xi;
		for (int j = 0; j < S[i]; j++) {
			v[i][j] = (rand() % 9999 + 1) / 100.0;
			w[i][j] = (rand() % 9999 + 1) / 100.0;
		}
	}
//	cout << "N = " << N << endl;
//	cout << "V = " << V << endl;
//	cout << "S = ";
//	for (int i = 0; i < N; i++)
//		cout << S[i] << ' ';
//	cout << endl;
//	for (int i = 0; i < N; i++) {
//		cout << (i == 0 ? "v = " : "    ");
//		for (int j = 0; j < S[i]; j++)
//			cout << v[i][j] << ' ';
//		cout << endl;
//	}
//	for (int i = 0; i < N; i++) {
//		cout << (i == 0 ? "w = " : "    ");
//		for (int j = 0; j < S[i]; j++)
//			cout << w[i][j] << ' ';
//		cout << endl;
//	}
	
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
		if (dp[opt] <= V) {
//			cout << "opt = " << opt * e * P / N << endl;
			break;
		}
	for (int i = N - 1, j = opt; i >= 0; i--)
		if (sol[i][j] > 0) {
			x[i][sol[i][j] - 1] = 1;
			j -= v[i][sol[i][j] - 1];
		}
//	for (int i = 0; i < N; i++) {
//		cout << (i == 0 ? "x = " : "    ");
//		for (int j = 0; j < S[i]; j++)
//			cout << x[i][j] << ' ';
//		cout << endl;
//	}
	clock_t et = clock();
	cout << 1.0 * (et - st) / CLOCKS_PER_SEC << endl;
	return 0;
}
