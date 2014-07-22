#include <stdio.h>

#define MAX_N 100000

unsigned int h[MAX_N + 1], S[MAX_N];

int main(int argc, char *argv[]) {
	unsigned int N, n, s;
	unsigned long long area, max_area;
	while (EOF != scanf("%u", &N) && N) {
		for (n = 0; n < N; ++n) scanf("%u", &h[n]);
		for (s = 0, n = 0, max_area = 0, h[N] = 0; n <= N; ) if (!s || h[n] >= h[S[s - 1]]) S[s++] = n++; else if (--s, (area = (((unsigned long long)h[S[s]]) * (!s ? n : n - S[s - 1] - 1))) > max_area) max_area = area;
		printf("%llu\n", max_area);
	}
	return 0;
}
