#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_N 100000
#define MAX_L 15    /* ceil(log2(20000)) */

unsigned int N, num_edge, e_idx, idx[MAX_N], depth[MAX_N], P[MAX_N], min_h[MAX_L + 1][MAX_N << 1], anc[MAX_L + 1][MAX_N];

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

void ins_vertex(const unsigned int u) {
	min_h[0][e_idx] = u;
	if (-1 == idx[u]) idx[u] = e_idx;
	++e_idx;
}

void euler_tour(const unsigned int u, const unsigned int p, const unsigned int current_depth) {
	struct edge *ptr;
	P[u] = p, depth[u] = current_depth, ins_vertex(u);
	for (ptr = adj[u]; ptr; ptr = ptr->next) if (p != ptr->v) euler_tour(ptr->v, u, current_depth + 1), ins_vertex(u);
}

void init_st(void) {
	unsigned int p, w, n;
	/* number of vert(ices) in tree: N, number of point(s) in Euler tour: (2N - 1) */
	for (p = 1, w = 1; (w << 1) + 1 < (N << 1); ++p, w <<= 1) for (n = 0; n + 1 < (N << 1); ++n) min_h[p][n] = (n + w + 1 < (N << 1) && depth[min_h[p - 1][n + w]] < depth[min_h[p - 1][n]] ? min_h[p - 1][n + w] : min_h[p - 1][n]);
}

unsigned int lca_via_rmq(const unsigned int u, const unsigned int v) {
	unsigned int A, B, w, p, tmp, s, t;
	if ((A = idx[u]) > (B = idx[v])) tmp = A, A = B, B = tmp;
	p = msb(w = B - A + 1);
	return depth[s = min_h[p - 1][A]] < depth[t = min_h[p - 1][B - (1 << (p - 1)) + 1]] ? s : t;
}

unsigned int lca(const unsigned int u, const unsigned int v) {
	unsigned int _u, _v, d_u, d_v;
	_u = u, _v = v, d_u = depth[u], d_v = depth[v];
	while (d_u > d_v) _u = P[_u], --d_u;
	while (d_v > d_u) _v = P[_v], --d_v;
	while (_u != _v) _u = P[_u], _v = P[_v];
	return _u;
}

int main(int argc, char *argv[]) {
	unsigned int Q, n, u, v;
	scanf("%u%u", &N, &Q);
	if (!N) return 0;
	memset(idx, 0xFF, sizeof(idx));
	for (num_edge = 0, n = 0; n + 1 < N; ++n) scanf("%u%u", &u, &v), ins_edge(u, v), ins_edge(v, u);
	/* assuming there exists 1 vertex labeled 0 */
	e_idx = 0, euler_tour(0, -1, 0), init_st();
	for (n = 0; n < Q; ++n) {
		scanf("%u%u", &u, &v);
		#ifdef DEBUG
			printf("lca of %u and %u\n", u, v);
			printf("lca(%u, %u) == %u\n", u, v, lca(u, v));
			printf("lca_via_rmq(%u, %u) == %u\n", u, v, lca_via_rmq(u, v));
		#endif
		assert(lca_via_rmq(u, v) == lca(u, v));
	}
	return 0;
}
