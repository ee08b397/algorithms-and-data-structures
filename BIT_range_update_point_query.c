#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#define NUM_ELEM 1024
#define MAX_VAL 512
#define NUM_TEST 65536

int arr[NUM_ELEM], delta[NUM_ELEM], initial_val[NUM_ELEM];

int query(const size_t idx) {
	int val;
	size_t n;
	for (val = initial_val[idx], n = idx + 1; n; n -= n & -n) val += delta[n - 1]; 
	return val;
}

void update(const size_t range_min, const size_t range_max, const int d) {
	size_t n;
	for (n = range_min + 1; n <= NUM_ELEM; n += n & -n) delta[n - 1] += d;
	for (n = range_max + 2; n <= NUM_ELEM; n += n & -n) delta[n - 1] -= d;
}

int main(int argc, char *argv[]) {
	int val;
	unsigned int T = NUM_TEST;
	size_t n, min, max, tmp;
	srand(time(0));
	memset(arr, 0, sizeof(arr)), memset(delta, 0, sizeof(delta)), memset(initial_val, 0, sizeof(initial_val));
	for (n = 0; n < NUM_ELEM; ++n) val = -MAX_VAL + rand() % (MAX_VAL << 1), arr[n] = val, initial_val[n] = val;
	while (T--) {
		min = rand() % NUM_ELEM, max = rand() % NUM_ELEM; if (max < min) tmp = min, min = max, max = tmp, val = -MAX_VAL + rand() % (MAX_VAL << 1);
		for (n = min; n <= max; ++n) arr[n] += val;
		update(min, max, val);
		for (n = 0; n < NUM_ELEM; ++n) assert(arr[n] == query(n));
	}
	return 0;
}
