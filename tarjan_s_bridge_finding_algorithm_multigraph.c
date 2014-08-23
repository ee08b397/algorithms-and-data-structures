#include <stdio.h>
#include <stdlib.h>

#define MAX_V 10000
#define MAX_E 100000

unsigned int V, E, num_edge, K, vis[MAX_V], idx[MAX_V], low[MAX_V], pr[MAX_V], inc[MAX_V], br[MAX_E];

struct end_pt {
	unsigned int v, idx;
	struct end_pt *next;
} e[MAX_E << 1], *adj[MAX_V];

struct spt {
	unsigned int u, v, idx;
} stack[MAX_V + (MAX_E << 1)];

int cmp(const void *const a, const void *const b) {
	return *((const unsigned int *const)a) < *((const unsigned int *const)b) ? -1 : 1;
}

void ins_edge(const unsigned int u, const unsigned int v, const unsigned int idx) {
	e[num_edge].v = v, e[num_edge].next = adj[u], e[num_edge].idx = idx, adj[u] = &e[num_edge++];
}

void tarjan_dfs(const unsigned int r) {
	unsigned int u, v, p_idx, current_idx, stack_size;
	struct end_pt *ptr;
	for (current_idx = 0, stack_size = 1, stack[0].u = -1, stack[0].v = r, stack[0].idx = -1, pr[r] = -1, inc[r] = -1; stack_size; ) {
		u = stack[stack_size - 1].u, v = stack[stack_size - 1].v, p_idx = stack[stack_size - 1].idx;
		if (v < MAX_V) {
			if (!vis[v]) {
				idx[v] = low[v] = current_idx++, vis[v] = 1;
				for (ptr = adj[v]; ptr; ptr = ptr->next) {
					if (ptr->idx == p_idx) continue;
					stack[stack_size].u = v, stack[stack_size].v = MAX_V + ptr->v, stack[stack_size++].idx = ptr->idx;
				}
			}else if (--stack_size, r != v) {
				if (low[v] < low[u]) low[u] = low[v]; 
				if (low[v] > idx[u]) br[K++] = inc[v];
			}
		}else {
			v -= MAX_V;
			if (!vis[v]) stack[stack_size - 1].v = v, pr[v] = u, inc[v] = p_idx; else if (--stack_size, idx[v] < low[u]) low[u] = idx[v];
		}
	}
}

int main(int argc, char *argv[]) {
	unsigned int T, i, u, v;
	scanf("%u", &T);
	while (T--) {
		num_edge = 0, scanf("%u%u", &V, &E);
		for (i = 0; i < V; ++i) vis[i] = 0, adj[i] = NULL;
		for (i = 0; i < E; ++i) scanf("%u%u", &u, &v), --u, --v, ins_edge(u, v, i + 1), ins_edge(v, u, i + 1);
		K = 0, tarjan_dfs(0), qsort(br, K, sizeof(unsigned int), cmp), printf("%u\n", K);
		for (i = 0; i < K; ++i) printf("%u%c", br[i], i + 1 == K ? '\n' : ' ');
		if (T) printf("\n");
	}
	return 0;
}
