#include <stdio.h>

#define MAX_V 1000
#define MAX_E 4000

unsigned int V, E, num_edge, vis[MAX_V], idx[MAX_V], low[MAX_V], p[MAX_V], stack[MAX_V << 1];

struct end_pt {
	unsigned int v;
	struct end_pt *next;
} e[MAX_E << 1], *adj[MAX_V];

void ins_edge(const unsigned int u, const unsigned int v) {
	e[num_edge].v = v, e[num_edge].next = adj[u], adj[u] = &e[num_edge++];
}

void tarjan_dfs(const unsigned int r) {
	unsigned int u, v, current_idx, stack_size;
	struct end_pt *ptr;
	for (current_idx = 0, stack_size = 1, stack[0] = r, p[r] = -1; stack_size; ) {
		if ((u = stack[--stack_size]) < MAX_V) {
			vis[u] = 1, idx[u] = low[u] = current_idx++;
			for (ptr = adj[u]; ptr; ptr = ptr->next) if (!vis[v = ptr->v]) stack[stack_size++] = v + MAX_V, p[v] = u, stack[stack_size++] = v; else if (v != p[u] && idx[v] < low[u]) low[u] = idx[v];
		}else {
			v = u - MAX_V, u = p[v];
			if (low[v] < low[u]) low[u] = low[v];
			if (low[v] > idx[u]) printf("%u %u\n", u, v);
		}
	}
}

int main(int argc, char *argv[]) {
	unsigned int i, u, v;
	num_edge = 0, scanf("%u%u", &V, &E);
	for (i = 0; i < V; ++i) vis[i] = 0;
	for (i = 0; i < E; ++i) scanf("%u%u", &u, &v), ins_edge(u, v), ins_edge(v, u);
	tarjan_dfs(0);
	return 0;
}
