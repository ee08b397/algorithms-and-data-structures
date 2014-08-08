#include <stdio.h>
#include <stdint.h>
#include <assert.h>

unsigned int ceil_log2(const uint64_t X) {
	static const uint64_t t[7] = {
		0xFFFFFFFF00000000ull,
		0x00000000FFFF0000ull,
		0x000000000000FF00ull,
		0x00000000000000F0ull,
		0x000000000000000Cull,
		0x0000000000000002ull,
		0x0000000000000001ull
	};
	unsigned int l, i, p;
	uint64_t x;
	for (x = X, p = 32, l = 0, i = 0; i < 7; ++i) {
		if (x & t[i]) l += p, x >>= p;
		p >>= 1;
	}
	return l + ((X & (X - 1)) ? 1 : 0);
}

int main(int argc, char *argv[]) {
	uint64_t x, p;
	printf("%u\n", ceil_log2(0));
	printf("%u\n", ceil_log2(1));
	printf("%u\n", ceil_log2(2));
	printf("%u\n", ceil_log2(3));
	printf("%u\n", ceil_log2(4));
	printf("%u\n", ceil_log2(5));
	printf("%u\n", ceil_log2(6));
	printf("%u\n", ceil_log2(7));
	printf("%u\n", ceil_log2(8));
	printf("%u\n", ceil_log2(9));
	printf("%u\n", ceil_log2(15));
	printf("%u\n", ceil_log2(16));
	printf("%u\n", ceil_log2(0x0FFFFFFF00000000ull));
	printf("%u\n", ceil_log2(0xFFFFFFFF00000000ull));
	printf("%u\n", ceil_log2(0x0FFFFFFF));
	printf("%u\n", ceil_log2(0xFFFFFFFF));
	printf("%u\n", ceil_log2(0xFFFFFFFF00000000ull));
	printf("%u\n", ceil_log2(0x00000000FFFFFFFFull));
	printf("%u\n", ceil_log2(0x000000009FFFFFFFull));
	printf("%u\n", ceil_log2(0x000000008FFFFFFFull));
	printf("%u\n", ceil_log2(0x000000007FFFFFFFull));
	printf("%u\n", ceil_log2(0xFFFFFFFF4FFFFFFFull));
	printf("%u\n", ceil_log2(0xFFFFFFFF9FFFFFFFull));
	printf("%u\n", ceil_log2(0xFFFFFFFFFFFFFFFFull));
	for (x = 7; x < 77777777; ++x) p = (1ull << ceil_log2(x)), assert(((x == (x & -x)) && p == x) || (p > x && (p >> 1) < x));
	return 0;
}
