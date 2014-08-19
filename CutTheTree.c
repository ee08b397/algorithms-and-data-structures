/* https://www.hackerrank.com/challenges/cut-the-tree */

#include <stdio.h>

#define MAX_N 100000

struct edge {
	unsigned int v;
	struct edge *next;
};

unsigned int sum, min_diff, val[MAX_N];
struct edge *adj[MAX_N], e[MAX_N << 1];

unsigned int find_min_diff(const unsigned int p, const unsigned int v) {
	unsigned int s, t, diff;
	struct edge *ptr;
	for (s = val[v], ptr = adj[v]; ptr; ptr = ptr -> next) if (p != ptr -> v) s += find_min_diff(v, ptr -> v); 
	if ((diff = ((t = sum - s) > s) ? t - s : s - t) < min_diff) min_diff = diff;
	return s;
}

int main(int argc, char *argv[]) {
	unsigned int N, n, u, v;
	struct edge *ptr;
	scanf("%u", &N);
	for (n = 0; n < N; ++n) adj[n] = NULL;
	for (sum = 0, n = 0; n < N; ++n) scanf("%u", &val[n]), sum += val[n];
	for (n = 0; n + 1 < N; ++n) scanf("%u%u", &u, &v), --u, --v, e[n << 1].v = v, e[n << 1].next = adj[u], adj[u] = &e[n << 1], e[(n << 1) | 1].v = u, e[(n << 1) | 1].next = adj[v], adj[v] = &e[(n << 1) | 1];
	for (min_diff = -1, ptr = adj[0]; ptr; ptr = ptr -> next) find_min_diff(0, ptr -> v);
	printf("%u\n", min_diff);
	return 0;
}
