/* https://www.hackerrank.com/challenges/vertical-sticks */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50

int cmp(const void *const a, const void *const b) {
	return *((const unsigned int *const)a) < *((const unsigned int *const)b) ? 1 : -1;
}

int main(int argc, char *argv[]) {
	unsigned int T, N, n, cnt, y[MAX_N];
	double expV;
	scanf("%u", &T); 
	while (T--) {
		scanf("%u", &N);
		for (n = 0; n < N; ++n) scanf("%u", &y[n]);
		qsort(y, N, sizeof(unsigned int), cmp);
		for (expV = 0, n = 1, cnt = 1; n < N; ++n) if (y[n] < y[n - 1]) expV += 1.0 * cnt * (N + 1) / (n + 1), cnt = 1; else ++cnt;
		expV += 1.0 * cnt * (N + 1) / (n + 1);
		printf("%.2f\n", expV);
	}
	return 0;
}
