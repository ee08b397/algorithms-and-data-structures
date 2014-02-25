#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 20
#define MAX_N 100005

/* arr: the original input, sorted: the original input sorted in ascending order */
int arr[MAX_N], sorted[MAX_N], tree[MAX_DEPTH][MAX_N];

/* num_left[i][j] : number of element(s) less than median among the first j elements in the i-th layer of the tree  */
unsigned int num_left[MAX_DEPTH][MAX_N];

int cmp(const void *const a, const void *const b) {
	return *((const int *const)a) < *((const int *const)b) ? -1 : 1;
}

/* initialize values in the $depth -th level of the tree with index(es) in range [start, end] */
/* median_freq : number of times the median occurs in input array */
void init(const unsigned int depth, const unsigned int start, const unsigned int end) {
	unsigned int mid = ((start + end) >> 1), l_idx = start, r_idx = mid + 1, median_freq = mid + 1 - start, p;
	for (p = start; p <= mid; ++p) if (sorted[p] < sorted[mid]) --median_freq; 
	for (p = start; p <= end; ++p) {
		num_left[depth][p] = (p == start ? 0 : num_left[depth][p - 1]);
		/* split current level of the tree with the median (with the 2 halves being "as equally as possible") */
		if (tree[depth][p] == sorted[mid]) {
			if (median_freq) --median_freq, ++num_left[depth][p], tree[depth + 1][l_idx++] = tree[depth][p]; else tree[depth + 1][r_idx++] = tree[depth][p];
		}else if (tree[depth][p] < sorted[mid]) ++num_left[depth][p], tree[depth + 1][l_idx++] = tree[depth][p]; else tree[depth + 1][r_idx++] = tree[depth][p];
	}
	if (start < end) {
		init(depth + 1, start, mid);
		init(depth + 1, mid + 1, end);
	}
}

/* returns the k-th largest element among all elements with index(es) in [min_query_idx, max_query_idx] in the input array */
unsigned int query(const unsigned int depth, const unsigned int start, const unsigned int end, const unsigned int min_query_idx, const unsigned int max_query_idx, const unsigned int k) {
	unsigned int s, ss, mid = ((start + end) >> 1);
	if (start == end) return tree[depth][start];
	if (start == min_query_idx) s = 0, ss = num_left[depth][max_query_idx]; /* <-- special case */ else s = num_left[depth][min_query_idx - 1], ss = num_left[depth][max_query_idx] - s;
	return ss >= k ? query(depth + 1, start, mid, start + s, start + s + ss - 1, k) : query(depth + 1, mid + 1, end, mid + 1 + min_query_idx - start - s, mid + 1 + max_query_idx - start - s - ss, k - ss);
}

int main(int argc, char *argv[]) {
	unsigned int p, n, m, l, r, k;
	scanf("%u%u", &n, &m);
	for (p = 1; p <= n; ++p) {
		scanf("%d", &arr[p]);
		tree[0][p] = sorted[p] = arr[p]; 
	}
	qsort(sorted + 1, n, sizeof(int), cmp);  
	/* for (p = 1; p <= n; ++p) printf("%d ", sorted[p]); printf("\n"); */
	init(0, 1, n);
	while (m--) {
		scanf("%u%u%u", &l, &r, &k);
		printf("%d\n", query(0, 1, n, l, r, k));
	}
	return 0;
}
