#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#define NUM_ELEM 1024
#define MAX_VAL 512
#define NUM_TEST 65536

int arr[NUM_ELEM], bit[NUM_ELEM], subtract_amt[NUM_ELEM];

int __point_query(const int *const q_arr, const size_t idx) {
	int val;
	size_t n;
	for (val = 0, n = idx + 1; n; n -= n & -n) val += q_arr[n - 1]; 
	return val;
}

int point_query(const size_t idx) {
	return __point_query(bit, idx);
}

int culumative_sum_query(const size_t idx) {
	return __point_query(bit, idx) * (idx + 1) - __point_query(subtract_amt, idx); 
}

int range_query(const size_t range_min, const size_t range_max) {
	int sum = culumative_sum_query(range_max);
	if (range_min) sum -= culumative_sum_query(range_min - 1);
	return sum;
}

void __update(int *const d_arr, const size_t idx, const int d) {
	size_t n;
	for (n = idx + 1; n <= NUM_ELEM; n += n & -n) d_arr[n - 1] += d;
}

void range_update(const size_t range_min, const size_t range_max, const int d) {
	__update(bit, range_min, d), __update(bit, range_max + 1, -d);
	if (range_min) __update(subtract_amt, range_min, d * range_min);
	__update(subtract_amt, range_max + 1, -d * (range_max + 1));
}

void point_update(const size_t idx, const int d) {
	range_update(idx, idx, d);
}

int main(int argc, char *argv[]) {
	int val, sum;
	unsigned int T = NUM_TEST;
	size_t n, idx, min, max, tmp;
	srand(time(0));
	memset(arr, 0, sizeof(arr)), memset(bit, 0, sizeof(bit)), memset(subtract_amt, 0, sizeof(subtract_amt));
	for (n = 0; n < NUM_ELEM; ++n) val = -MAX_VAL + rand() % (MAX_VAL << 1), arr[n] = val, point_update(n, val);
	while (T--) {
		min = rand() % NUM_ELEM, max = rand() % NUM_ELEM; if (max < min) tmp = min, min = max, max = tmp, val = -MAX_VAL + rand() % (MAX_VAL << 1);
		for (n = min; n <= max; ++n) arr[n] += val;
		range_update(min, max, val);
		for (n = 0; n < NUM_ELEM; ++n) assert(arr[n] == point_query(n));
		if (min) val = -MAX_VAL + rand() % (MAX_VAL << 1), idx = rand() % min, arr[idx] += val, point_update(idx, val); 
		if (max + 1 < NUM_ELEM) val = -MAX_VAL + rand() % (MAX_VAL << 1), idx = max + rand() % (NUM_ELEM - 1 - max), arr[idx] += val, point_update(idx, val); 
		val = -MAX_VAL + rand() % (MAX_VAL << 1), idx = min + rand() % (max - min + 1), arr[idx] += val, point_update(idx, val); 
		for (sum = 0, n = min; n <= max; ++n) sum += arr[n];
		assert(sum == range_query(min, max));
	}
	return 0;
}
