#include <stdio.h>

#define MAX_N 100000
#define MAX_L 17
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int V[MAX_N + 1], S[MAX_N];
unsigned int l, r, m_l, m_r;
unsigned long long val, max_val, sum[MAX_N];

int main(int argc, char *argv[]) {
	unsigned int N, n, s;
	scanf("%u", &N);
	for (V[N] = -1, n = 0; n < N; ++n) scanf("%d", &V[n]);
	for (sum[0] = V[0], n = 1; n < N; ++n) sum[n] = sum[n - 1] + V[n];
	for (s = 0, n = 0, max_val = 0; n <= N; ) if (!s || V[n] >= V[S[s - 1]]) S[s++] = n++; else if (--s, r = n - 1, l = (s ? S[s - 1] + 1 : 0), (val = ((unsigned long long)V[S[s]]) * (sum[r] - (l ? sum[l - 1] : 0))) > max_val) max_val = val, m_l = l, m_r = r; 
	printf("%llu\n%u %u\n", max_val, m_l + 1, m_r + 1);
	return 0;
}
