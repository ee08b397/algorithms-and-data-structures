#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define LOG_MAX_N 16

struct node {
	int key, priority;
	unsigned int idx;
};

/* min_priority_idx : RMQ table formed by priority values */
/* note: parent, left_child, right_child are 1-based */
unsigned int N, parent[MAX_N], left_child[MAX_N], right_child[MAX_N], min_priority_idx[LOG_MAX_N][MAX_N];
struct node nd[MAX_N];

int cmp_key(const void * const a, const void * const b) {  /* sort nodes by key, in ascending order */
	return ((const struct node *const)a) -> key < ((const struct node *const)b) -> key ? -1 : 1;
}

unsigned int msb(unsigned int x) {
	static const unsigned int bval[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
	unsigned int r = 0;
	if (x & 0xFFFF0000) { r += 16; x >>= 16; }
	if (x & 0x0000FF00) { r += 8; x >>= 8; }
	if (x & 0x000000F0) { r += 4; x >>= 4; }
	return r + bval[x];
}

/* note: parent_idx is 1-based */
unsigned int build_tree(const unsigned int parent_idx, const unsigned int min_idx, const unsigned int max_idx) {
	unsigned int root, root_idx, p, idx_a, idx_b;
	p = msb(max_idx - min_idx + 1);
	root = nd[idx_a = min_priority_idx[p - 1][min_idx]].priority < nd[idx_b = min_priority_idx[p - 1][max_idx - (1 << (p - 1)) + 1]].priority ? idx_a : idx_b;
	root_idx = nd[root].idx;
	parent[root_idx] = parent_idx;
	left_child[root_idx] = root > min_idx ? build_tree(root_idx + 1, min_idx, root - 1) + 1 : 0;
	right_child[root_idx] = root < max_idx ? build_tree(root_idx + 1, root + 1, max_idx) + 1 : 0;
	return root_idx;
}

int main(int argc, char *argv[]) {
	unsigned int n, w, p, idx_a, idx_b;
	scanf("%u", &N);   /* assuming N > 0 */
	for (n = 0; n < N; ++n) scanf("%d%d", &nd[n].key, &nd[n].priority), nd[n].idx = n, min_priority_idx[0][n] = n;
	qsort(nd, N, sizeof(struct node), cmp_key);
	for (p = 1, w = 1; p < LOG_MAX_N; ++p, w <<= 1) for (n = 0; n < N; ++n) min_priority_idx[p][n] = n + w < N ? nd[idx_a = min_priority_idx[p - 1][n]].priority < nd[idx_b = min_priority_idx[p - 1][n + w]].priority ? idx_a : idx_b : min_priority_idx[p - 1][n];  /* build RMQ sparse table with priority values */
	build_tree(0, 0, N - 1);
	printf("YES\n");
	for (n = 0; n < N; ++n) printf("%u %u %u\n", parent[n], left_child[n], right_child[n]);
	return 0;
}
