#include <stdio.h>
#include <stdlib.h>

#define MAX_K 100
#define MAX_H 10000

int comp(const void *a, const void *b) {
	return *((unsigned int *)a) < *((unsigned int *)b) ? -1 : 1;
}

unsigned int compute_sg(const unsigned int h, const unsigned int k, const unsigned int S[], unsigned int sg[], unsigned int mex[]) {
	unsigned int i;
	/* for (i = 0; i <= MAX_H; ++i) mex[i] = 0; */
	for (i = 0; i < k; ++i) if (S[i] <= h) mex[sg[h - S[i]]] = h; else break;
	for (i = 0; i <= MAX_H; ++i) if (mex[i] != h) return (sg[h] = i);
	return (sg[h] = i);
}

int main(int argc, char *argv[]) {
	unsigned int i, k, m, l, h, max_n, nim_sum, sg[MAX_H + 1], S[MAX_K], mex[MAX_H + 1];
	while (1) {
		scanf("%u", &k);
		if (!k) return 0;
		for (i = 0; i <= MAX_H; ++i) mex[i] = 0;
		for (i = 0; i < k; ++i) scanf("%u", &S[i]);
		qsort(S, k, sizeof(unsigned int), comp);
		for (i = 0; i < S[0]; ++i) sg[i] = 0;
		sg[S[0]] = 1; 
		max_n = S[0];
		scanf("%u", &m);
		while (m--) {
			scanf("%u", &l); 
			nim_sum = 0;
			while (l--) {
				scanf("%u", &h);
				if (h > max_n) {
					for (i = max_n + 1; i <= h; ++i) compute_sg(i, k, S, sg, mex);
					max_n = h;
				}
				nim_sum ^= sg[h];
			}
			printf(nim_sum ? "W" : "L");
		}
		printf("\n");
	}
	return 0;
}
