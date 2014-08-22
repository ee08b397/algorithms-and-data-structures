#include <stdio.h>
#include <stdlib.h>

#define MAX_V 200100
#define MAX_E 200100
#define IN "bridges.in"
#define OUT "bridges.out"

unsigned int V, E, num_edge, K, vis[MAX_V], idx[MAX_V], low[MAX_V], p[MAX_V], inc[MAX_V], stack[MAX_V << 1], br[MAX_E];

struct end_pt {
	unsigned int v, idx;
	struct end_pt *next;
} e[MAX_E << 1], *adj[MAX_V];

int cmp(const void *const a, const void *const b) {
	return *((const unsigned int *const)a) < *((const unsigned int *const)b) ? -1 : 1;
}

void ins_edge(const unsigned int u, const unsigned int v, const unsigned int idx) {
	e[num_edge].v = v, e[num_edge].next = adj[u], e[num_edge].idx = idx, adj[u] = &e[num_edge++];
}

void tarjan_dfs(const unsigned int r) {
	unsigned int u, v, current_idx, stack_size;
	struct end_pt *ptr;
	for (current_idx = 0, stack_size = 1, stack[0] = r, inc[r] = -1; stack_size; ) {
		if ((u = stack[--stack_size]) < MAX_V) {
			vis[u] = 1, idx[u] = low[u] = current_idx++;
			for (ptr = adj[u]; ptr; ptr = ptr->next) if (!vis[v = ptr->v]) stack[stack_size++] = v + MAX_V, p[v] = u, inc[v] = ptr->idx, stack[stack_size++] = v; else if (inc[u] != ptr->idx && idx[v] < low[u]) low[u] = idx[v];
		}else {
			v = u - MAX_V, u = p[v];
			if (low[v] < low[u]) low[u] = low[v];
			if (low[v] > idx[u]) br[K++] = inc[v];
		}
	}
}

int main(int argc, char *argv[]) {
	unsigned int i, u, v;
	FILE *in, *out;
	in = fopen(IN, "r"), out = fopen(OUT, "w");
	num_edge = 0, fscanf(in, "%u%u", &V, &E);
	for (i = 0; i < V; ++i) vis[i] = 0;
	for (i = 0; i < E; ++i) fscanf(in, "%u%u", &u, &v), --u, --v, ins_edge(u, v, i + 1), ins_edge(v, u, i + 1);
	K = 0, tarjan_dfs(0), qsort(br, K, sizeof(unsigned int), cmp), fprintf(out, "%u\n", K);
	for (i = 0; i < K; ++i) fprintf(out, "%u%c", br[i], i + 1 == K ? '\n' : ' ');
	fclose(in), fclose(out);
	return 0;
}
