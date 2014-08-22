#include <stdio.h>

#define MAX_V 100000
#define MAX_E 200000

unsigned int V, E, num_edge, idx[MAX_V], low[MAX_V], vis[MAX_V], parent[MAX_V], stack[MAX_V << 1];

struct end_pt {
	unsigned int v;
	struct end_pt *next;
} e[MAX_E << 1], *adj[MAX_V];

void ins_edge(const unsigned int a, const unsigned int b) {
	e[num_edge].v = b, e[num_edge].next = adj[a], adj[a] = &e[num_edge++];
}

void tarjan_dfs(const unsigned int root) {
	unsigned int u, v, c, stack_size, current_idx;
	struct end_pt *ptr;
	current_idx = 0, stack_size = 1, parent[root] = -1, stack[0] = root;
	while (stack_size) {
		if ((v = stack[--stack_size]) >= MAX_V) {    /* post-processing */
			v -= MAX_V;
			if (-1 != (u = parent[v])) {
				if (low[v] < low[u]) low[u] = low[v];
				if (idx[u] < low[v]) printf("%u %u\n", u, v);    /* bridge found */
			}
		}else for (stack[stack_size++] = v + MAX_V, vis[v] = 1, low[v] = idx[v] = current_idx++, ptr = adj[v]; ptr; ptr = ptr->next) if (!vis[c = ptr-> v]) parent[c] = v, stack[stack_size++] = c; else if (c != parent[v] && idx[c] < low[v]) low[v] = idx[c];   /* pre-processing */
	}
}

int main(int argc, char *argv[]) {
	unsigned int i, a, b;
	while (EOF != scanf("%u%u", &V, &E)) {
		for (i = 0; i < V; ++i) adj[i] = NULL, vis[i] = 0;
		for (num_edge = 0, i = 0; i < E; ++i) scanf("%u%u", &a, &b), ins_edge(a, b), ins_edge(b, a); 
		tarjan_dfs(0);
	}
	return 0;
}
