#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define LOG_MAX_N 16

struct node {
	int key, priority;
	unsigned int idx;
};

unsigned int parent[MAX_N + 1], left_child[MAX_N + 1], right_child[MAX_N + 1], nd_map[MAX_N + 1]; /* note : parent, left_child, right_child are 1-based */
struct node nd[MAX_N];

int cmp_key(const void * const a, const void * const b) {  /* sort nodes by key, in ascending order */
	return ((const struct node *const)a) -> key < ((const struct node *const)b) -> key ? -1 : 1;
}

/* note: parent_idx is 1-based */
void insert_node(const unsigned int idx) { /* note : idx is 0-based */
	const int current_priority = nd[idx].priority;
	unsigned int p_idx, prev_p_idx = 0;
	for (p_idx = nd[idx - 1].idx; p_idx && nd[nd_map[p_idx]].priority > current_priority; prev_p_idx = p_idx, p_idx = parent[p_idx]); 
	if (!p_idx)
		parent[prev_p_idx] = nd[idx].idx,
		left_child[nd[idx].idx] = prev_p_idx;
	else
		left_child[nd[idx].idx] = right_child[p_idx],
		parent[right_child[p_idx]] = nd[idx].idx,
		right_child[p_idx] = nd[idx].idx,
		parent[nd[idx].idx] = p_idx; 
}

int main(int argc, char *argv[]) {
	unsigned int n, N;
	scanf("%u", &N);   /* assuming N > 0 */
	for (n = 0; n < N; ++n) scanf("%d%d", &nd[n].key, &nd[n].priority), nd[n].idx = n + 1, left_child[n + 1] = 0, right_child[n + 1] = 0, parent[n + 1] = 0;
	qsort(nd, N, sizeof(struct node), cmp_key);
	for (n = 0; n < N; ++n) nd_map[nd[n].idx] = n;   /* stores inverse permutation of the sorted order */ 
	for (n = 1; n < N; ++n) insert_node(n);
	printf("YES\n");
	for (n = 1; n <= N; ++n) printf("%u %u %u\n", parent[n], left_child[n], right_child[n]);
	return 0;
}
