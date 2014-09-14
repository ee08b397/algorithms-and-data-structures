#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_N 100000
#define MAX_L 15    /* ceil(log2(20000)) */
#define MAX_Q 5

unsigned int N, num_edge, e_idx, idx[MAX_N], depth[MAX_N], P[MAX_N], path[MAX_N], st[MAX_L][MAX_N];

struct edge {
	unsigned int v;
	struct edge *next;
} e[MAX_N << 1], *adj[MAX_N];

unsigned int msb(unsigned int x) {
	static const unsigned int bval[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
	unsigned int r;
	r = 0;
	if (x & 0xFFFF0000) { r += 16; x >>= 16; }
	if (x & 0x0000FF00) { r += 8; x >>= 8; }
	if (x & 0x000000F0) { r += 4; x >>= 4; }
	return r + bval[x];
}

void ins_edge(const unsigned int u, const unsigned int v) {
	e[num_edge].v = v, e[num_edge].next = adj[u], adj[u] = &e[num_edge++];
}

void dfs(const unsigned int u, const unsigned int p, const unsigned int current_depth) {
	unsigned int d, l;
	struct edge *ptr;
	depth[u] = current_depth, path[current_depth] = u, P[u] = p;
	for (l = 0, d = 1; d <= current_depth; ++l, d <<= 1) st[l][u] = path[current_depth - d];
	for (ptr = adj[u]; ptr; ptr = ptr->next) if (p != ptr->v) dfs(ptr->v, u, current_depth + 1);
}

unsigned int kth_parent(const unsigned int u, const unsigned int k) {
	unsigned int d, p, r;
	for (r = u, d = k; d; ) p = d & -d, r = st[msb(p) - 1][r], d -= p;
	return r;
}

int main(int argc, char *argv[]) {
	unsigned int n, u, v, r, k;
	scanf("%u", &N);
	if (!N) return 0;
	memset(idx, 0xFF, sizeof(idx));
	for (num_edge = 0, n = 0; n + 1 < N; ++n) scanf("%u%u", &u, &v), ins_edge(u, v), ins_edge(v, u);
	/* assuming there exists 1 vertex labeled 0 */
	dfs(0, -1, 0);
	for (u = 0; u < N; ++u) for (k = 0, r = u; -1 != r; r = P[r], ++k) assert(kth_parent(u, k) == r); 
	return 0;
}
