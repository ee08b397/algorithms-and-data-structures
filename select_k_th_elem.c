#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000001

int A[MAX_N];

size_t partition(const size_t min_idx, const size_t max_idx, const size_t pivot_idx, int *const A) {
	int p, tmp;
	size_t st_idx, i;
	for (p = A[pivot_idx], A[pivot_idx] = A[max_idx], A[max_idx] = p, st_idx = min_idx, i = min_idx; i < max_idx; ++i) if (A[i] < p) tmp = A[st_idx],
A[st_idx] = A[i], A[i] = tmp, ++st_idx;
	tmp = A[max_idx], A[max_idx] = A[st_idx], A[st_idx] = tmp;
	return st_idx;
}

int select_k_th_elem(const size_t min_idx, const size_t max_idx, const size_t K, int *const A) {
	size_t pivot_idx, _min_idx, _max_idx;
	for (_min_idx = min_idx, _max_idx = max_idx; ; ) {
		if (_min_idx == _max_idx) return A[_min_idx];
		pivot_idx = partition(_min_idx, _max_idx, _min_idx + rand() % (_max_idx + 1 - _min_idx)/* ((_max_idx - _min_idx) >> 1)*/, A);
		if (K < pivot_idx) _max_idx = pivot_idx - 1; else if (K > pivot_idx) _min_idx = pivot_idx + 1; else return A[K];
	}
	return A[K];
}

int main(int argc, char *argv[]) {
	unsigned int N, n;
	scanf("%u", &N);
	for (n = 0; n < N; ++n) scanf("%d", &A[n]);
	printf("%d\n", select_k_th_elem(0, N - 1, N >> 1, A));
	return 0;
}

