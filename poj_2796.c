#include <stdio.h>

#define MAX_N 100000
#define MAX_L 17
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int V[MAX_N + 1], S[MAX_N], min_v[MAX_L][MAX_N + 1];
unsigned int l, r, m_l, m_r;
unsigned long long val, max_val, sum[MAX_N];

unsigned int msb(unsigned int x) {
	static const unsigned int bval[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
	unsigned int r = 0;
	if (x & 0xFFFF0000) { r += 16; x >>= 16; }
	if (x & 0x0000FF00) { r += 8; x >>= 8; }
	if (x & 0x000000F0) { r += 4; x >>= 4; }
	return r + bval[x];
}

int main(int argc, char *argv[]) {
	unsigned int N, n, s, p, w;
	scanf("%u", &N);
	for (V[N] = -1, min_v[0][N] = -1, n = 0; n < N; ++n) scanf("%d", &V[n]), min_v[0][n] = V[n];
	for (sum[0] = V[0], n = 1; n < N; ++n) sum[n] = sum[n - 1] + V[n];
	for (p = 1, w = 1; p < MAX_L; ++p, w <<= 1) for (n = 0; n <= N; ++n) min_v[p][n] = (n + w <= N ? MIN(min_v[p - 1][n], min_v[p - 1][n + w]) : min_v[p - 1][n]);
	for (s = 0, n = 0, max_val = 0; n <= N; ) if (!s || V[n] >= V[S[s - 1]]) S[s++] = n++; else if (--s, p = msb((r = n - 1) - (l = (s ? S[s - 1] + 1 : 0)) + 1), (val = MIN(min_v[p - 1][l], min_v[p - 1][r - (1 << (p - 1)) + 1]) * (sum[r] - (l ? sum[l - 1] : 0))) > max_val) max_val = val, m_l = l, m_r = r; 
	printf("%llu\n%u %u\n", max_val, m_l + 1, m_r + 1);
	return 0;
}
