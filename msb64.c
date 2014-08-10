#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

uint64_t msb(const uint64_t N) {
	unsigned int cp, p, k;
	uint64_t n;
	const static uint64_t mask[7] = {
		0xFFFFFFFF00000000ull,
		0x00000000FFFF0000ull,
		0x000000000000FF00ull,
		0x00000000000000F0ull,
		0x000000000000000Cull,
		0x0000000000000002ull,
		0x0000000000000001ull
	};
	if (!N) return 0;
	for (n = N, cp = 32, p = 0, k = 0; k < 7; ++k, cp >>= 1) if (n & mask[k]) p += cp, n >>= cp;
	return 1ull << p;
}

int main(int argc, char *argv[]) {
	uint64_t i, g;
	const uint64_t T[12] = {0, 1, 2, 17, 16, 31, 32, 33, 65537, -1, 999, ~0x10};
	for (i = 0; i < 12; ++i) printf("msb(%"SCNu64") == %"SCNu64"\n", T[i], msb(T[i]));
	for (i = 2; i < 0x0FFFFFFFull; ++i) g = msb(i), assert(g <= i && (g << 1) > i && g == (g & -g));
	for (i = 0x7FFFFFFFFF000000ull; i < 0x7FFFFFFFFFFFFFFFull; ++i) g = msb(i), assert(g <= i && (g << 1) > i && g == (g & -g));
	return 0;
}

