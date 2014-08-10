#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX_N 100000

int cmp(const void *const a, const void *const b) {
	return *((const uint64_t *const)a) < *((const uint64_t *const)b) ? 1 : -1;
}

unsigned int msb(const uint64_t N) {
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
	return p;
}

int main(int argc, char *argv[]) {
	unsigned int N, r, s;
	uint64_t tmp, ans, pvt, row[MAX_N];
	scanf("%u", &N);
	for (r = 0; r < N; ++r) scanf("%"SCNu64, &row[r]);
	qsort(row, N, sizeof(uint64_t), cmp);
	/* proceed greedily from high-order to low-order bits, using elementary row operation(s) with
	   addition mod 2 to determine the largest xor sum (which is simply a bit-vector within the
	   span of the row space) */
	for (r = 0, pvt = 1ull << msb(row[0]); pvt && r < N; pvt >>= 1) {
		for (s = r; s < N && !(row[s] & pvt); ++s);
		/* current bit cannot be set to 1, so continue */
		if (s == N) continue;
		/* pivoting */
		if (s != r) tmp = row[r], row[r] = row[s], row[s] = tmp;
		for (s = 0; s < N; ++s) if (s != r && (row[s] & pvt)) row[s] ^= row[r];
		++r;
	}
	for (ans = 0, r = 0; r < N; ++r) ans ^= row[r];
	printf("%"PRIu64"\n", ans);
	return 0;
}
