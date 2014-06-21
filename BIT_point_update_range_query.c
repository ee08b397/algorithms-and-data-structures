#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#define NUM_ELEM 1024
#define MAX_VAL 512
#define NUM_TEST 65536

int arr[NUM_ELEM], bit[NUM_ELEM];

int query(const size_t range_min, const size_t range_max) {
	int sum;
	size_t n;
	for (sum = 0, n = range_max + 1; n; n -= n & -n) sum += bit[n - 1];
	for (n = range_min; n; n -= n & -n) sum -= bit[n - 1];
	return sum;
}

void update(const size_t idx, const int delta) {
	size_t n;
	for (n = idx + 1; n <= NUM_ELEM; n += n & -n) bit[n - 1] += delta;
}

int main(int argc, char *argv[]) {
	int val, sum;
	unsigned int T = NUM_TEST;
	size_t n, min, max, idx, tmp;
	srand(time(0));
	memset(arr, 0, sizeof(arr)), memset(bit, 0, sizeof(bit));
	for (n = 0; n < NUM_ELEM; ++n) val = -MAX_VAL + rand() % (MAX_VAL << 1), arr[n] = val, update(n, val);
	while (T--) {
		min = rand() % NUM_ELEM, max = rand() % NUM_ELEM; if (max < min) tmp = min, min = max, max = tmp;
		if (min) val = -MAX_VAL + rand() % (MAX_VAL << 1), idx = rand() % min, arr[idx] += val, update(idx, val); 
		if (max + 1 < NUM_ELEM) val = -MAX_VAL + rand() % (MAX_VAL << 1), idx = max + rand() % (NUM_ELEM - 1 - max), arr[idx] += val, update(idx, val); 
		val = -MAX_VAL + rand() % (MAX_VAL << 1), idx = min + rand() % (max - min + 1), arr[idx] += val, update(idx, val); 
		for (sum = 0, n = min; n <= max; ++n) sum += arr[n];
		assert(sum == query(min, max));
	}
	return 0;
}
