#include <stdio.h>
#include <string.h>

#define MAX_N 900
#define MAX_L 11
#define MAX_VTX_LEN 15

static unsigned int N, Q, stack_size, in_deg[MAX_N], vis[MAX_N], P[MAX_N], idx[MAX_N], lca_freq[MAX_N], stack[MAX_N << 2], st[MAX_L][MAX_N << 1];

static struct node {
	unsigned int n, l;
	struct node *S, *next;
} v[MAX_N];

unsigned int msb(unsigned int x) {
	unsigned int r;
	static const unsigned int B[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
	r = 0;
	if (x & 0xFFFF0000) { r += 16; x >>= 16; }
	if (x & 0x0000FF00) { r += 8; x >>= 8; }
	if (x & 0x000000F0) { r += 4; x >>= 4; }
	return r + B[x];
}

void compute_st(const unsigned int r) {
	unsigned int etr_idx, current_level, s, p, w, n;
	struct node *ptr;
	for (etr_idx = 0, stack_size = 1, stack[0] = r; stack_size; ) if (!vis[s = stack[stack_size - 1]]) for (idx[s] = etr_idx, st[0][etr_idx] = s, current_level = v[s].l, ++etr_idx, vis[s] = 1, ptr = v[s].S; ptr; ptr = ptr->next) P[ptr->n] = s, v[ptr->n].l = current_level + 1, stack[stack_size++] = ptr->n; else --stack_size, -1 == P[s] || (st[0][etr_idx] = P[s], ++etr_idx);
	for (p = 1, w = 1; (w << 1) + 1 < (N << 1); ++p, w <<= 1) for (n = 0; n + 1 < (N << 1); ++n) st[p][n] = (n + w + 1 < (N << 1) && v[st[p - 1][n + w]].l < v[st[p - 1][n]].l ? st[p - 1][n + w] : st[p - 1][n]);
}

unsigned int lca(const unsigned int a, const unsigned int b) {
	unsigned int A, B, w, p, tmp, s, t;
	if ((A = idx[a]) > (B = idx[b])) tmp = A, A = B, B = tmp;
	p = msb(w = B - A + 1);
	return v[s = st[p - 1][A]] .l < v[t = st[p - 1][B - (1 << (p - 1)) + 1]].l ? s : t;
}

int main(int argc, char *argv[]) {
	char vtx[MAX_VTX_LEN + 1];
	unsigned int i, j, r, l, s, offset;
	while (EOF != scanf("%u", &N)) {
		for (memset(in_deg, 0, N * sizeof(unsigned int)), memset(vis, 0, N * sizeof(unsigned int)),  memset(lca_freq, 0, N * sizeof(unsigned int)), i = 0; i < N; ++i) {
			for (scanf("%s", vtx), offset = 0, r = 0; '0' <= vtx[offset] && '9' >= vtx[offset]; r *= 10, r += vtx[offset++] - '0'); --r;
			for (offset += 2, l = 0; '0' <= vtx[offset] && '9' >= vtx[offset]; l *= 10, l += vtx[offset++] - '0');
			for (v[r].n = r, v[r].S = NULL, j = 0; j < l; ++j) scanf("%u", &s), --s, ++in_deg[s], v[s].next = v[r].S, v[r].S = &v[s];
		}
		for (r = 0; r < N; ++r) if (!in_deg[r]) { P[r] = -1, v[r].l = 0, compute_st(r); break; }
		for (scanf("%u", &Q); Q--; ) {
			for (scanf("%s", vtx), offset = 1, r = 0; '0' <= vtx[offset] && '9' >= vtx[offset]; r *= 10, r += vtx[offset++] - '0'); --r;
			for (++offset, s = 0; '0' <= vtx[offset] && '9' >= vtx[offset]; s *= 10, s += vtx[offset++] - '0'); --s;
			++lca_freq[lca(r, s)];
		}
		for (i = 0; i < N; ++i) if (lca_freq[i]) printf("%u:%u\n", i + 1, lca_freq[i]); 
	}
	return 0;
}
