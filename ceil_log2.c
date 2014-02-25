#include <stdio.h>

unsigned int ceil_log2(const unsigned long long __x) {
	static const unsigned long long t[6] = {
		0xFFFFFFFF00000000ull,
		0x00000000FFFF0000ull,
		0x000000000000FF00ull,
		0x00000000000000F0ull,
		0x000000000000000Cull,
		0x0000000000000002ull
	};

	unsigned long long x = __x;
	unsigned int y = (((x & (x - 1)) == 0) ? 0 : 1), i, j, k;

	for (j = 0x20, i = 0; i < 6; ++i) {
		k = (((x & t[i]) == 0) ? 0 : j);
		y += k;
		x >>= k;
		j >>= 1;
	}

	return y;
}

int main(int argc, char *argv[]) {
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
	return 0;
}
