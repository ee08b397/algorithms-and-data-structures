#include <stdio.h>

#define MAX_N 30000

unsigned int min_heap_size, max_heap_size, M, N, i, u[MAX_N + 1];
int min_heap[MAX_N + 1], max_heap[MAX_N + 1], A[MAX_N];

void ins(const int sgn, const int elem, int h[], unsigned int *const sz) {  /* sgn < 0 -> min heap */
	int tmp;
	unsigned int p, q;
	for (h[++*sz] = elem, p = *sz, q = p >> 1; q; p >>= 1, q >>= 1) if (sgn < 0 ? h[q] > h[p] : h[q] < h[p]) tmp = h[p], h[p] = h[q], h[q] = tmp; else return;
}

int del(const int sgn, int h[], unsigned int *const sz) {
	int tmp, r;
	unsigned int p, q, s; 
	for (r = h[1], h[1] = h[(*sz)--], p = 1, q = 2; q <= *sz; q = p << 1) {
		if (sgn < 0 ? h[p] <= h[q] && ((q | 1) > *sz || h[p] <= h[q | 1]) : h[p] >= h[q] && ((q | 1) > *sz || h[p] >= h[q | 1])) break;
		tmp = h[s = ((q | 1) > *sz ? q : ((sgn < 0 ? h[q] < h[q | 1] : h[q] > h[q | 1]) ? q : q | 1))], h[s] = h[p], h[p] = tmp, p = s; 
	}
	return r;
}

int main(int argc, char *argv[]) {
	int v;
	unsigned int j, k;
	min_heap_size = 0, max_heap_size = 0, i = 1;
	scanf("%u%u", &N, &M);
	for (k = 0; k < N; ++k) scanf("%d", &A[k]); 
	for (u[0] = 0, j = 1; j <= M; ++j) scanf("%u", &u[j]); 
	for (j = 1; j <= M; ++j) {
		for (k = u[j - 1]; k < u[j]; ++k) {
			ins(1, A[k], max_heap, &max_heap_size);
			if (max_heap_size + 1 > j) ins(-1, del(1, max_heap, &max_heap_size), min_heap, &min_heap_size);
		}
		ins(1, v = del(-1, min_heap, &min_heap_size), max_heap, &max_heap_size), printf("%d\n", max_heap[1]);
	}
	return 0;
}
