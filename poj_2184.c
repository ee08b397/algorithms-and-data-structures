#include <stdio.h>
#include <limits.h>

#define MAX_N 100
#define MAX_VAL 100000

int S[MAX_N], F[MAX_N];
int mem[2][(MAX_VAL << 1) + 1];

int main(int argc, char *argv[]) {
	int N, n, v, s, alt, max;
	scanf("%u", &N);
	for (n = 0; n < N; ++n) scanf("%d%d", &S[n], &F[n]);
	for (v = 0; v <= (MAX_VAL << 1); ++v) mem[0][v] = INT_MIN;
	mem[0][S[0] + MAX_VAL] = F[0];
	for (n = 1; n < N; ++n) {
		for (v = 0; v <= (MAX_VAL << 1); ++v) mem[n & 1][v] = mem[~n & 1][v];
		if (F[n] > mem[n & 1][s = MAX_VAL + S[n]]) mem[n & 1][s] = F[n];
		for (v = 0; v <= (MAX_VAL << 1); ++v) if (INT_MIN != mem[~n & 1][v] && (alt = mem[~n & 1][v] + F[n]) > mem[n & 1][s = v + S[n]]) mem[n & 1][s] = alt; 
	}
	for (max = 0, v = MAX_VAL; v <= (MAX_VAL << 1); ++v) if (mem[~N & 1][v] >= 0 && (alt = v - MAX_VAL + mem[~N & 1][v]) > max) max = alt;
	printf("%d\n", max);
	return 0;
}
