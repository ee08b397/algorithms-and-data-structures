#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

unsigned int N, A[MAX_N + 2];

int cmp(const void *const a, const void *const b) {
	return *((const unsigned int *const)a) < *((const unsigned int *const)b) ? -1 : 1;
}

unsigned int find_predecessor(const unsigned int elem) {
	unsigned int min, max, mid;
	if (elem < A[0]) return 0;  /* special case: return 0 even if no predecessor exists */
	for (min = 0, max = N - 1, mid = (min + max) >> 1; min < max; mid = (min + max + 1) >> 1) if (A[mid] < elem) min = mid; else if (A[mid] > elem) max = mid - 1; else return mid;
	return max;
}

unsigned int find_successor(const unsigned int elem) {
	unsigned int min, max, mid;
	if (elem > A[N - 1]) return N - 1;  /* special case: return (N - 1) even if no successor exists */
	for (min = 0, max = N - 1, mid = (min + max) >> 1; min < max; mid = (min + max) >> 1) if (A[mid] > elem) max = mid; else if (A[mid] < elem) min = mid + 1; else return mid;
	return max;
}

int main(int argc, char *argv[]) {
	unsigned int P, Q, p_idx, q_idx, n, max_min_L1_dist, alt, m, alt_M, M;
	scanf("%u", &N);
	for (n = 0; n < N; ++n) scanf("%u", &A[n]);
	qsort(A, N, sizeof(unsigned int), cmp);
	scanf("%u%u", &P, &Q);
	max_min_L1_dist = 0, M = A[0], p_idx = find_successor(P), q_idx = find_predecessor(Q);
	if (P < A[0]) max_min_L1_dist = A[0] - P, M = P; else if (p_idx && (alt = ((m = (A[p_idx - 1] + A[p_idx]) >> 1) < P ? A[p_idx] - (alt_M = P) : A[p_idx] - (alt_M = m))) > max_min_L1_dist) max_min_L1_dist = alt, M = alt_M; 
	if (Q > A[N - 1] && (alt = Q - A[N - 1]) > max_min_L1_dist) max_min_L1_dist = alt, M = Q; else if (q_idx + 1 < N && (alt = ((m = (A[q_idx] + A[q_idx + 1]) >> 1) > Q ? (alt_M = Q) - A[q_idx] : (alt_M = m) - A[q_idx])) > max_min_L1_dist) max_min_L1_dist = alt, M = alt_M;
	for (n = p_idx; n < q_idx; ++n) if ((alt = ((alt_M = (A[n] + A[n + 1]) >> 1) - A[n])) > max_min_L1_dist) max_min_L1_dist = alt, M = alt_M; 
	printf("%u\n", M);
	return 0;
}
