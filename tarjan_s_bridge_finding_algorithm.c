#include <stdio.h>

#define MAX_V 1000
#define MAX_E 1000

unsigned int V, E, num_edge, vis[MAX_V], idx[MAX_V], low[MAX_V], /*p[MAX_V], */bcc_out_deg[MAX_V], stack[MAX_V + MAX_E][2];

unsigned int current_idx;

struct end_pt {
	unsigned int v;
	struct end_pt *next;
} e[MAX_E << 1], *adj[MAX_V];

void ins_edge(const unsigned int u, const unsigned int v) {
	e[num_edge].v = v, e[num_edge].next = adj[u], adj[u] = &e[num_edge++];
}

/*
void tarjan_dfs(const unsigned int u, const unsigned int p) {
	unsigned int v;
	struct end_pt *ptr;
	idx[u] = low[u] = current_idx++, vis[u] = 1;
	for (ptr = adj[u]; ptr; ptr = ptr->next) {
		if (!vis[v = ptr->v]) {
			tarjan_dfs(v, u);
			if (low[v] < low[u]) low[u] = low[v];
		}else if (v != p && idx[v] < low[u]) low[u] = idx[v];
	}
}
*/

void tarjan_dfs(const unsigned int r) {
	unsigned int u, p, current_idx, stack_size;
	struct end_pt *ptr;
	for (current_idx = 0, stack_size = 1, stack[0][0] = r, stack[0][1] = -1; stack_size; ) {
		u = stack[stack_size - 1][0], p = stack[stack_size - 1][1];
		if (u < MAX_V) {
			if (!vis[u]) {
				idx[u] = low[u] = current_idx++, vis[u] = 1;
				for (ptr = adj[u]; ptr; ptr = ptr->next) {
					if (ptr->v == p) continue;
					stack[stack_size][0] = MAX_V + ptr->v, stack[stack_size++][1] = u;
				}
			}else if (--stack_size, r != u && low[u] < low[p]) low[p] = low[u]; 
		}else {
			u -= MAX_V;
			if (!vis[u]) stack[stack_size - 1][0] = u; else if (--stack_size, idx[u] < low[p]) low[p] = idx[u];
		}
	}
}

int main(int argc, char *argv[]) {
	unsigned int i, u, v, num_unreachable;
	struct end_pt *ptr;
	num_edge = 0, scanf("%u%u", &V, &E);
	for (i = 0; i < V; ++i) vis[i] = 0, bcc_out_deg[i] = 0;
	for (i = 0; i < E; ++i) scanf("%u%u", &u, &v), --u, --v, ins_edge(u, v), ins_edge(v, u);
	current_idx = 0, tarjan_dfs(0);
	for (i = 0; i < V; ++i) for (ptr = adj[i]; ptr; ptr = ptr->next) if (low[i] != low[ptr->v]) ++bcc_out_deg[low[i]];
	for (num_unreachable = 0, i = 0; i < V; ++i) if (1 == bcc_out_deg[i]) ++num_unreachable;
	printf("%u\n", (num_unreachable + 1) >> 1);
	return 0;
}
