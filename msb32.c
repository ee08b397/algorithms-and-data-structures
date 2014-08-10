#include <stdio.h>
#include <assert.h>

unsigned int msb(const unsigned int N) {
	unsigned int n, p, cp, k;
	const static unsigned int mask[6] = {
		0xFFFF0000,
		0x0000FF00,
		0x000000F0,
		0x0000000C,
		0x00000002,
		0x00000001
	};
	if (!N) return 0;
	for (n = N, cp = 16, p = 0, k = 0; k < 6; ++k, cp >>= 1) if (n & mask[k]) p += cp, n >>= cp;
	return 1 << p;
}

int main(int argc, char *argv[]) {
	unsigned int i, m;
	const unsigned int T[12] = {0, 1, 2, 17, 16, 31, 32, 33, 65537, -1, 999, ~0x10};
	for (i = 0; i < 12; ++i) printf("msb(%u) == %u\n", T[i], msb(T[i]));
	for (i = 2; i < 0x0FFFFFFF; ++i) m = msb(i), assert(m <= i && (m << 1) > i && m == (m & -m));
	for (i = 0x8FFFFFFF; i < 0xFFFFFFFF; ++i) m = msb(i), assert(m <= i && ((1ull * m) << 1) > 1ull * i && m == (m & -m));
	return 0;
}

