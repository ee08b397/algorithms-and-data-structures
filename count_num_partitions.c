#include <stdio.h>

#define MAX_N 200

unsigned long long nPart(const unsigned int N, const unsigned int K, unsigned long long P[][MAX_N]) {
	if (K > N) {
		return 0;
	}
	if (P[N - 1][K - 1]) {
		return P[N - 1][K - 1];
	}
	P[N - 1][K - 1] = nPart(N - 1, K - 1, P) + nPart(N - K, K, P);
	return P[N - 1][K - 1];
}

int main(int argc, char *argv[]) {
	unsigned int n, k, N, K;
	unsigned long long P[MAX_N][MAX_N];
	for (n = 0; n < MAX_N; ++n) {    /* 1 truck */
		P[n][0] = 1;
	}
	for (k = 0; k < MAX_N; ++k) {    /* (k + 1) trucks(s) and (k + 1) computer(s) */ 
		P[k][k] = 1;
	}
	for (n = 0; n < MAX_N; ++n) {    /* more than 1 and less than (n + 1) truck(s) and (n + 1) computer(s) */ 
		for (k = 1; k < n; ++k) {
			P[n][k] = 0;
		}
	}
	while (1) {
		scanf("%u %u\n", &N, &K);
		if (!N && !K) {
			return 0;
		}
		printf("%llu\n", nPart(N, K, P));
	}
	return 0;
}
