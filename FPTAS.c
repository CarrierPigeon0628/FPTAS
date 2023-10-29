#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));
	
	double e = 0.01;
	
	// Generate a sample.
//	int N = rand() % 100 + 1;
	int N = 20;  // for testing
	double V = (rand() % 9999 + 1) / 100.0;
	int* S = (int*)malloc(N * sizeof(int));
	double** v = (double**)malloc(N * sizeof(double*)), ** w = (double**)malloc(N * sizeof(double*));
	int** x = (int**)malloc(N * sizeof(int*));
	int i, j, k;
	for (i = 0; i < N; i++) {
//		S[i] = rand() % 100 + 1;
		S[i] = 20;  // for testing
		v[i] = (double*)malloc(S[i] * sizeof(double));
		w[i] = (double*)malloc(S[i] * sizeof(double));
		x[i] = (int*)malloc(S[i] * sizeof(int));
		for (j = 0; j < S[i]; j++) {
			v[i][j] = (rand() % 9999 + 1) / 100.0;
			w[i][j] = (rand() % 9999 + 1) / 100.0;
			x[i][j] = 0;
		}
	}
//	printf("N = %d\n", N);
//	printf("V = %f\n", V);
//	printf("S = ");
//	for (i = 0; i < N; i++)
//		printf("%d ", S[i]);
//	printf("\n");
//	for (i = 0; i < N; i++) {
//		printf(i == 0 ? "v = " : "    ");
//		for (j = 0; j < S[i]; j++)
//			printf("%f ", v[i][j]);
//		printf("\n");
//	}
//	for (i = 0; i < N; i++) {
//		printf(i == 0 ? "w = " : "    ");
//		for (j = 0; j < S[i]; j++)
//			printf("%f ", w[i][j]);
//		printf("\n");
//	}
	
	// FPTAS
	clock_t st = clock();
	double P = 0;
	for (i = 0; i < N; i++)
		for (j = 0; j < S[i]; j++)
			if (P < v[i][j])
				P = v[i][j];
	for (i = 0; i < N; i++)
		for (j = 0; j < S[i]; j++)
			v[i][j] = (int)(v[i][j] * N / e / P);
	double* dp = (double*)malloc((N * (int)(N / e) + 1) * sizeof(double));
	dp[0] = 0;
	for (i = 1; i <= N * (int)(N / e); i++)
		dp[i] = 100;
	int** sol = (int**)malloc(N * sizeof(int*));
	for (i = 0; i < N; i++) {
		sol[i] = (int*)malloc((N * (int)(N / e) + 1) * sizeof(int));
		for (j = N * (int)(N / e); j >= 0; j--) {
			sol[i][j] = 0;
			for (k = 0; k < S[i]; k++)
				if (j >= v[i][k] && dp[j - (int)(v[i][k])] + w[i][k] < dp[j]) {
					dp[j] = dp[j - (int)(v[i][k])] + w[i][k];
					sol[i][j] = k + 1;
				}
		}
	}
	int opt;
	for (opt = N * (int)(N / e); opt >= 0; opt--)
		if (dp[opt] <= V) {
//			printf("opt = %f\n", opt * e * P / N);
			break;
		}
	for (i = N - 1, j = opt; i >= 0; i--)
		if (sol[i][j] > 0) {
			x[i][sol[i][j] - 1] = 1;
			j -= v[i][sol[i][j] - 1];
		}
//	for (i = 0; i < N; i++) {
//		printf(i == 0 ? "x = " : "    ");
//		for (j = 0; j < S[i]; j++)
//			printf("%d ", x[i][j]);
//		printf("\n");
//	}
	clock_t et = clock();
	printf("%f\n", 1.0 * (et - st) / CLOCKS_PER_SEC);
	
	for(i = 0; i < N; i++) {
		free(sol[i]);
		free(x[i]);
		free(w[i]);
		free(v[i]);
	}
	free(sol);
	free(dp);
	free(x);
	free(w);
	free(v);
	free(S);
	return 0;
}
