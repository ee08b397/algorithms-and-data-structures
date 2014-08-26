#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000000

unsigned int A[MAX_N];

static inline unsigned int partition(const unsigned int min_idx, const unsigned int max_idx, const unsigned int pivot_idx) {
	unsigned int st_idx, i, p, tmp;
	for (p = A[pivot_idx], A[pivot_idx] = A[max_idx], A[max_idx] = p, st_idx = min_idx, i = min_idx; i < max_idx; ++i) if (A[i] < p) tmp = A[st_idx],
A[st_idx] = A[i], A[i] = tmp, ++st_idx;
	tmp = A[max_idx], A[max_idx] = A[st_idx], A[st_idx] = tmp;
	return st_idx;
}

unsigned int select_k_th_elem(const unsigned int min_idx, const unsigned int max_idx, const unsigned int K) {
	unsigned int pivot_idx, _min_idx, _max_idx;
	for (_min_idx = min_idx, _max_idx = max_idx; ; ) {
		if (_min_idx == _max_idx) return A[_min_idx];
		pivot_idx = partition(_min_idx, _max_idx, _min_idx + rand() % (_max_idx + 1 - _min_idx)/* ((_max_idx - _min_idx) >> 1)*/);
		if (K < pivot_idx) _max_idx = pivot_idx - 1; else if (K > pivot_idx) _min_idx = pivot_idx + 1; else return A[K];
	}
	return A[K];
}

int main(int argc, char *argv[]) {
	unsigned int n, a, b, mod, K;
	scanf("%u%u%u%u", &a, &b, &mod, &K);
	for (n = 0; n < MAX_N; ++n) a = 31014 * (a & 65535) + (a >> 16), b = 17508 * (b & 65535) + (b >> 16), A[n] = ((a << 16) + b) % mod;
	printf("%u\n", select_k_th_elem(0, MAX_N - 1, K - 1));
	return 0;
}

