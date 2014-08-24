#include <stdio.h>

#define MAX_V 1000
#define MAX_E 2000  /* 4 * 1000 / 2 */

unsigned int V, E, num_edge, K, vis[MAX_V], idx[MAX_V], low[MAX_V], inc[MAX_V], is_bridge[MAX_E], incl[MAX_E];

struct end_pt {
	unsigned int v, idx;
	struct end_pt *next;
} e[MAX_E << 1], *adj[MAX_V];

struct spt {
	unsigned int u, v, idx;
} stack[MAX_V + (MAX_E << 1)];

void ins_edge(const unsigned int u, const unsigned int v, const unsigned int idx) {
	e[num_edge].v = v, e[num_edge].next = adj[u], e[num_edge].idx = idx, adj[u] = &e[num_edge++];
}

void tarjan_dfs(const unsigned int r) {
	unsigned int u, v, p_idx, current_idx, stack_size;
	struct end_pt *ptr;
	for (current_idx = 0, stack_size = 1, stack[0].u = -1, stack[0].v = r, stack[0].idx = -1, inc[r] = -1; stack_size; ) {
		u = stack[stack_size - 1].u, v = stack[stack_size - 1].v, p_idx = stack[stack_size - 1].idx;
		if (v < MAX_V) {
			if (!vis[v]) {
				idx[v] = low[v] = current_idx++, vis[v] = 1;
				for (ptr = adj[v]; ptr; ptr = ptr->next) {
					if (p_idx == ptr->idx) continue;
					stack[stack_size].u = v, stack[stack_size].v = MAX_V + ptr->v, stack[stack_size++].idx = ptr->idx;
				}
			}else if (--stack_size, r != v) {
				if (low[v] < low[u]) low[u] = low[v]; 
				if (idx[u] < low[v]) is_bridge[inc[v]] = 1;
			}
		}else {
			v -= MAX_V;
			if (!vis[v]) stack[stack_size - 1].v = v, inc[v] = p_idx; else if (--stack_size, idx[v] < low[u]) low[u] = idx[v];
		}
	}
}

void print_ans(const unsigned int r) {
	unsigned int u, v, p_idx, stack_size;
	struct end_pt *ptr;
	for (stack_size = 1, stack[0].u = -1, stack[0].v = r, stack[0].idx = -1; stack_size; ) {
		if ((v = stack[stack_size - 1].v) < MAX_V) {
			vis[v] = 1, --stack_size;
			for (ptr = adj[v]; ptr; ptr = ptr->next) {
				stack[stack_size].u = v, stack[stack_size].v = MAX_V + ptr->v, stack[stack_size++].idx = ptr->idx;
			}
		}else {
			u = stack[stack_size - 1].u, v -= MAX_V, p_idx = stack[stack_size - 1].idx;
			if (!incl[p_idx]) {
				incl[p_idx] = 1;
				printf("%u %u\n", u + 1, v + 1);
				if (is_bridge[p_idx]) printf("%u %u\n", v + 1, u + 1);
				if (!vis[v]) stack[stack_size - 1].v = v; else --stack_size;
			}else --stack_size;
		}
	}
}

int main(int argc, char *argv[]) {
	unsigned int T, i, u, v;
	for (T = 1; EOF != scanf("%u%u", &V, &E); ++T) {
		if (!V && !E) break;
		for (i = 0; i < V; ++i) vis[i] = 0, adj[i] = NULL;
		for (num_edge = 0, i = 0; i < E; ++i) incl[i] = 0, is_bridge[i] = 0, scanf("%u%u", &u, &v), --u, --v, ins_edge(u, v, i), ins_edge(v, u, i);
		for (i = 0; i < V; ++i) if (!vis[i]) tarjan_dfs(i);
		for (i = 0; i < V; ++i) vis[i] = 0;
		printf("%u\n\n", T);
		for (i = 0; i < V; ++i) if (!vis[i]) print_ans(i);
		printf("#\n");
	}
	return 0;
}
