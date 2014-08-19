#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 15000

unsigned int edge_idx[MAX_M];

struct edge {
	unsigned int u, v, L;
} e[MAX_M];

struct comp {
	unsigned int size;
	struct comp *p;
} c[MAX_N];

int cmp(const void *const a, const void *const b) {
	return ((const struct edge *const)a)->L < ((const struct edge *const)b)->L ? -1 : 1;
}

struct comp * comp_find(struct comp *const pf) {
	struct comp *ptr;
	for (ptr = pf; ptr->p; ptr = ptr->p); 
	return ptr; 
}

int comp_union(struct comp *const pa, struct comp *const pb) {
	struct comp *ra, *rb;
	if ((ra = comp_find(pa)) == (rb = comp_find(pb))) return 0;
	if (ra->size < rb->size) ra->p = rb, rb->size += ra->size; else rb->p = ra, ra->size += rb->size;
	return 1;
}

int main(int argc, char *argv[]) {
	unsigned int N, M, n, m, ne, max_L;
	while (EOF != scanf("%u%u", &N, &M)) {
		for (n = 0; n < N; ++n) c[n].size = 1, c[n].p = NULL;
		for (m = 0; m < M; ++m) scanf("%u%u%u", &e[m].u, &e[m].v, &e[m].L);
		qsort(e, M, sizeof(struct edge), cmp);
		for (ne = 0, max_L = 0, m = 0; ne + 1 < N && m < M; ++m) {
			if (comp_union(&c[e[m].u - 1], &c[e[m].v - 1])) {
				edge_idx[ne++] = m;
				if (e[m].L > max_L) max_L = e[m].L;
			}
		}
		printf("%u\n%u\n", max_L, ne);
		for (m = 0; m < ne; ++m) printf("%u %u\n", e[edge_idx[m]].u, e[edge_idx[m]].v);
	}
	return 0;
}
