#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_N 10000
#define MAX_L 15    /* ceil(log2(20000)) */
#define MAX_Q 8

unsigned int N, num_edge, e_idx, idx[MAX_N], depth[MAX_N], dist[MAX_N], cp[MAX_N], min_h[MAX_L][MAX_N << 1], p_st[MAX_L][MAX_N];

struct edge {
	unsigned int v, L;
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

void ins_edge(const unsigned int u, const unsigned int v, const unsigned int L) {
	e[num_edge].v = v, e[num_edge].L = L, e[num_edge].next = adj[u], adj[u] = &e[num_edge++];
}

void ins_vertex(const unsigned int u) {
	min_h[0][e_idx] = u;
	if (-1 == idx[u]) idx[u] = e_idx;
	++e_idx;
}

void euler_tour(const unsigned int u, const unsigned int p, const unsigned int current_depth, const unsigned int current_dist) {
	unsigned int l, d;
	struct edge *ptr;
	depth[u] = current_depth, dist[u] = current_dist, ins_vertex(u);
	for (cp[current_depth] = u, l = 0, d = 1; d <= current_depth; ++l, d <<= 1) p_st[l][u] = cp[current_depth - d]; 
	for (ptr = adj[u]; ptr; ptr = ptr->next) if (p != ptr->v) euler_tour(ptr->v, u, current_depth + 1, current_dist + ptr->L), ins_vertex(u);
}

void init_st(void) {
	unsigned int p, w, n;
	/* number of vert(ices) in tree: N, number of point(s) in Euler tour: (2N - 1) */
	for (p = 1, w = 1; (w << 1) + 1 < (N << 1); ++p, w <<= 1) for (n = 0; n + 1 < (N << 1); ++n) min_h[p][n] = (n + w + 1 < (N << 1) && depth[min_h[p - 1][n + w]] < depth[min_h[p - 1][n]] ? min_h[p - 1][n + w] : min_h[p - 1][n]);
}

unsigned int kth_parent(const unsigned int u, const unsigned int k) {
	unsigned int d, p, r;
	for (r = u, d = k; d; ) p = d & -d, r = p_st[msb(p) - 1][r], d -= p;
	return r;
}

unsigned int lca(const unsigned int u, const unsigned int v) {
	unsigned int A, B, w, p, tmp, s, t;
	if ((A = idx[u]) > (B = idx[v])) tmp = A, A = B, B = tmp;
	p = msb(w = B - A + 1);
	return depth[s = min_h[p - 1][A]] < depth[t = min_h[p - 1][B - (1 << (p - 1)) + 1]] ? s : t;
}

int main(int argc, char *argv[]) {
	char q[MAX_Q + 1];
	unsigned int T, n, u, v, L, l, k;
	scanf("%u", &T);
	while (T--) {
		scanf("%u", &N);
		memset(idx, 0xFF, sizeof(idx));
		memset(adj, 0, N * sizeof(struct edge *));
		for (num_edge = 0, n = 0; n + 1 < N; ++n) scanf("%u%u%u", &u, &v, &L), --u, --v, ins_edge(u, v, L), ins_edge(v, u, L);
		e_idx = 0, euler_tour(0, -1, 0, 0), init_st();
		while(1) {
			scanf("%s", q);
			if (!strcmp(q, "DONE")) {
				break;
			}else {
				scanf("%u%u", &u, &v), --u, --v, l = lca(u, v);
				if (!strcmp(q, "DIST")) {
					printf("%u\n", (dist[u] + dist[v]) - (dist[l] << 1));
				}else {
					scanf("%u", &k), --k;
					printf("%u\n", (k > depth[u] - depth[l] ? kth_parent(v, (depth[v] - depth[l]) - (k - (depth[u] - depth[l]))) : kth_parent(u, k)) + 1);
				}
			}
		}
	}
	return 0;
}
