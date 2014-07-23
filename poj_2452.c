#include <stdio.h>

#define MAX_N 50000
#define MAX_L 16

unsigned int h[MAX_N + 1], S[MAX_N], max_idx[MAX_L][MAX_N + 1];

unsigned int msb(unsigned int x) {
	static const unsigned int bval[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
	unsigned int r = 0;
	if (x & 0xFFFF0000) { r += 16; x >>= 16; }
	if (x & 0x0000FF00) { r += 8; x >>= 8; }
	if (x & 0x000000F0) { r += 4; x >>= 4; }
	return r + bval[x];
}

int main(int argc, char *argv[]) {
	unsigned int N, n, s, p, w, len, max_len, a, b;
	while (EOF != scanf("%u", &N)) {
		for (h[N] = 0, max_idx[0][N] = N, n = 0; n < N; ++n) scanf("%u", &h[n]), max_idx[0][n] = n;
		for (p = 1, w = 1; p < MAX_L; ++p, w <<= 1) for (n = 0; n <= N; ++n) max_idx[p][n] = (n + w <= N ? (h[a = max_idx[p - 1][n]] > h[b = max_idx[p - 1][n + w]] ? a : b) : max_idx[p - 1][n]);
		for (s = 0, n = 0, max_len = 0; n <= N; ) if (!s || h[n] >= h[S[s - 1]]) S[s++] = n++; else if (--s, p = msb(n - S[s] + 1), (len = (h[a = max_idx[p - 1][S[s]]] > h[b = max_idx[p - 1][n - (1 << (p - 1)) + 1]] ? a : b) - S[s]) > max_len) max_len = len; 
		if (max_len) printf("%u\n", max_len); else printf("-1\n");
	}
	return 0;
}
