#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <limits.h>
#include <assert.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#define MAX_N 7331
#define MAX_INCR 512
#define NUM_TEST 65536
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int t[MAX_N << 2], delta[MAX_N << 2], arr[MAX_N];

void init(void) {
	memset(t, 0, sizeof(t)), memset(delta, 0, sizeof(delta));
}

int push_down(const unsigned int node_num, const unsigned int min, const unsigned int max) {
	if (min > max) return 0;
	if (delta[node_num]) {
		t[node_num] += delta[node_num];
		if (min < max) delta[node_num << 1] += delta[node_num], delta[(node_num << 1) | 1] += delta[node_num];
		delta[node_num] = 0;
	}
	return 1;
}

void update(const unsigned int node_num, const unsigned int min, const unsigned int max, const unsigned int start, const unsigned int end, const int diff) {
	unsigned int mid;
	if (!push_down(node_num, min, max) || end < min || max < start) return;
	if (start <= min && max <= end) {
		t[node_num] += diff;
		if (min < max) delta[node_num << 1] += diff, delta[(node_num << 1) | 1] += diff;
		return;
	}
	mid = (min + max) >> 1, update(node_num << 1, min, mid, start, end, diff), update((node_num << 1) | 1, mid + 1, max, start, end, diff), t[node_num] = MAX(t[node_num << 1], t[(node_num << 1) | 1]);
}

int query(const unsigned int node_num, const unsigned int min, const unsigned int max, const unsigned int start, const unsigned int end) {
	unsigned int mid;
	if (!push_down(node_num, min, max) || end < min || max < start) return INT_MIN;
	if (start <= min && max <= end) return t[node_num]; 
	return mid = (min + max) >> 1, MAX(query(node_num << 1, min, mid, start, end), query((node_num << 1) | 1, mid + 1, max, start, end)); 
}

void update_arr(const unsigned int start, const unsigned int end, const int diff) {
	unsigned int i;
	for (i = start; i <= end; ++i) arr[i] += diff; 
}

int query_arr(const unsigned int start, const unsigned int end) {
	unsigned int i;
	int max;
	for (max = arr[start], i = start + 1; i <= end; ++i) if (arr[i] > max) max = arr[i];
	return max;
}

int main(int argc, char *argv[]) {
	int diff;
	unsigned int start, end, t = NUM_TEST;
	srand(time(0)); init(), memset(arr, 0, sizeof(arr));
	while (t--) {
		start = rand() % MAX_N, end = start + rand() % (MAX_N - start), diff = -MAX_INCR + rand() % (MAX_INCR << 1), update(1, 0, MAX_N - 1, start, end, diff), update_arr(start, end, diff);
		#ifdef DEBUG
		printf("[%u, %u]\n%d == %d\n", start, end, query(1, 0, MAX_N - 1, start, end), query_arr(start, end));
		#endif
		assert(query(1, 0, MAX_N - 1, start, end) == query_arr(start, end));
		start = rand() % MAX_N, end = start + rand() % (MAX_N - start);
		#ifdef DEBUG
		printf("%d == %d\n\n", query(1, 0, MAX_N - 1, start, end), query_arr(start, end));
		#endif
		assert(query(1, 0, MAX_N - 1, start, end) == query_arr(start, end));
	}
	return 0;
}
