#include <stdio.h>

#define MAX_V 10000
#define MAX_E 100000
#define MOD 1000000000

struct end_pt {
	unsigned int u, v;
	struct end_pt *next;
};

unsigned int V, E, top, next_idx, num_scc, q[MAX_E], deg[MAX_V], conn[MAX_V], has_loop[MAX_V], idx[MAX_V], lowlink[MAX_V], stack[MAX_V], in_stack[MAX_V], scc_size[MAX_V], scc_map[MAX_V];
struct end_pt edge[MAX_E], scc_edge[MAX_E], *ptr, *adj[MAX_V], *scc_adj[MAX_V];

/* Tarjan's strongly connected components algorithm */
void scc(const unsigned int v) {
	unsigned int w;
	struct end_pt *ptr;
	lowlink[v] = idx[v] = next_idx++, stack[top++] = v, in_stack[v] = 1;
	for (ptr = adj[v]; ptr; ptr = ptr -> next) {
		if (-1 == (idx[w = ptr -> v])) {
			scc(w);
			if (lowlink[w] < lowlink[v]) lowlink[v] = lowlink[w];
		}else if (in_stack[w] && idx[w] < lowlink[v]) lowlink[v] = idx[w];
	}
	/* this maps each vertex in the current strongly-connected component to the root vertex of the component and also adds that root vertex to an array */
	if (lowlink[v] == idx[v]) {
		/* printf("BEGIN SCC:\n"); */
		for (scc_size[num_scc] = 0, w = -1; w != v; ) scc_map[w = stack[--top]] = num_scc, in_stack[w] = 0, ++scc_size[num_scc]/*, printf("%u ", w + 1)*/; 
		/* printf("\nEND SCC\n\n"); */
		++num_scc;
	}
}

int main(int argc, char *argv[]) {
	unsigned int v, e, a, b, w, num_scc_edge, qfront, qback;
	scanf("%u%u", &V, &E);
	for (v = 0; v < V; ++v) idx[v] = -1, in_stack[v] = 0, adj[v] = NULL;
	for (e = 0; e < E; ++e) scanf("%u%u", &a, &b), edge[e].u = --a, edge[e].v = --b, edge[e].next = adj[a], adj[a] = &edge[e];
	for (top = 0, next_idx = 0, num_scc = 0, v = 0; v < V; ++v) if (-1 == idx[v]) scc(v);
	for (v = 0; v < num_scc; ++v) deg[v] = 0, conn[v] = 0, has_loop[v] = 0, scc_adj[v] = NULL;
	for (e = 0, num_scc_edge = 0; e < E; ++e) if ((a = scc_map[edge[e].u]) != (b = scc_map[edge[e].v])) scc_edge[num_scc_edge].v = b, scc_edge[num_scc_edge].next = scc_adj[a], scc_adj[a] = &scc_edge[num_scc_edge], ++deg[b], ++num_scc_edge; 
	for (qfront = 0, qback = 0, v = 0; v < num_scc; ++v) if (!deg[v]) q[qback++] = v/* , printf("push %u\n", v + 1) */;
	for (v = scc_map[0], conn[v] = 1, has_loop[v] = (scc_size[v] > 1); qback > qfront; ) {
		v = q[qfront++]/*, printf("pop %u\n", v + 1) */;
		for (ptr = scc_adj[v]; ptr; ptr = ptr -> next) {
			if ((conn[w = ptr -> v] += conn[v]) >= MOD) conn[w] -= MOD;
			has_loop[w] |= (has_loop[v] | (scc_size[w] > 1)); 
			if (!--deg[w]) q[qback++] = w/*, printf("push %u\n", ptr -> v + 1)*/;
		}
	}
	if (has_loop[v = scc_map[V - 1]]) printf("INFINITE PATHS\n"); else printf("%u\n", conn[v]);
	return 0;
}
