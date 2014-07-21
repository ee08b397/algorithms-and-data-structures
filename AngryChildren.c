#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000 
#define MAX_DIFF 1000000000

unsigned int cnd[MAX_N];

int cmp(const void *const a, const void *const b) {
	return *((const unsigned int *const)a) < *((const unsigned int *const)b) ? -1 : 1;
}

int main(int argc, char *Argv[]) {
	unsigned int N, K, n, diff, min_diff;
	scanf("%u%u", &N, &K), min_diff = MAX_DIFF;
	for (n = 0; n < N; ++n) scanf("%u", &cnd[n]);
	qsort(cnd, N, sizeof(unsigned int), cmp);
	for (n = 0; n + K - 1 < N; ++n) if ((diff = cnd[n + K - 1] - cnd[n]) < min_diff) min_diff = diff; 
	printf("%u\n", min_diff);
	return 0;
}
