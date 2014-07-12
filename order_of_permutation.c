#include <stdio.h>
#include <string.h>
#define MAX_N 355  /* see https://oeis.org/A000793 (Landau's function) */

unsigned int N, P[MAX_N], cyc[MAX_N];

unsigned long long __gcd(const unsigned long long a, const unsigned long long b) {
	unsigned long long c;
	if (!(c = a % b)) return b;
	return __gcd(b, c);
}

unsigned long long gcd(const unsigned long long a, const unsigned long long b) {
	return a > b ? __gcd(a, b) : __gcd(b, a);
}

unsigned long long lcm(const unsigned long long a, const unsigned long long b) {
	return (a * b) / gcd(a, b);
}

int main(int argc, char *argv[]) {
	unsigned int n, c, cyc_len;
	unsigned long long ord;
	while (EOF != scanf("%u\n", &N)) {
		for (n = 0; n < N; ++n) scanf("%u", &P[n]), --P[n]; /* assuming input is 1-based */
		memset(cyc, 0, sizeof(cyc));
		for (ord = 1, n = 0; n < N; ++n) {
			if (cyc[n]) continue;
			for (cyc_len = 1, c = P[n]; c != n; ++cyc_len) cyc[c] = 1, c = P[c]; 
			ord = lcm(ord, cyc_len);
		}
		printf("%llu\n", ord);
	}
	return 0;
}
