#include <stdio.h>

#define MAX_N 50000
#define LOG_MAX_N 16

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* application of the sparse table (ST) algorithm */

unsigned int msb(unsigned int x) {
	static const unsigned int bval[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
	unsigned int r = 0;
	if (x & 0xFFFF0000) { r += 16; x >>= 16; }
	if (x & 0x0000FF00) { r += 8; x >>= 8; }
	if (x & 0x000000F0) { r += 4; x >>= 4; }
	return r + bval[x];
}

int main(int argc, char *argv[]) {
	/*
	    min_h[j][i]: min height within range [ i, i + 2 ^ j )
	    max_h[j][i]: max height within range [ i, i + 2 ^ j )
	*/
	unsigned int N, Q, n, h, p, w, A, B, min_h[LOG_MAX_N][MAX_N], max_h[LOG_MAX_N][MAX_N];
	scanf("%u%u", &N, &Q);
	for (n = 0; n < N; ++n) {
		scanf("%u", &h);
		min_h[0][n] = h;
		max_h[0][n] = h;
	}
	for (p = 1, w = 1; p < LOG_MAX_N; ++p, w <<= 1) {
		for (n = 0; n < N; ++n) {
			min_h[p][n] = MIN(min_h[p - 1][n], n + w < N ? min_h[p - 1][n + w] : 0);
			max_h[p][n] = MAX(max_h[p - 1][n], n + w < N ? max_h[p - 1][n + w] : 0);
		}
	}
	while (Q--) {
		scanf("%u%u", &A, &B);
		--A; --B;
		w = B - A + 1;   /* note: w >= 1, msb(w) >= 1 */
		p = msb(w);
		printf("%u\n", MAX(max_h[p - 1][A], max_h[p - 1][B - (1 << (p - 1)) + 1]) - MIN(min_h[p - 1][A], min_h[p - 1][B - (1 << (p - 1)) + 1]));
	}
	return 0;
}
