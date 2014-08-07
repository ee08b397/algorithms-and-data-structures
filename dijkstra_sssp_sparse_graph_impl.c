/* POJ 3255 Accepted 42644K 141MS GCC 1991B 2014-06-26 12:31:48 */
#include <stdio.h>
#include <string.h>

#define MAX_V 5000    /* max number of vertices */
#define MAX_E 200000  /* max number of directed edges */
#define INF 0x4FFFFFFF

struct node {
	unsigned int v;
	int dist;
};

unsigned int V, E, heap_size, deg[MAX_V], vis[MAX_V], G[MAX_V][MAX_V];
int dist[MAX_V][2], L[MAX_V][MAX_V];
struct node heap[MAX_E << 1];

void init(void) {
	heap_size = 0;
	heap[0].v = -1, heap[0].dist = -1;
	memset(deg, 0, sizeof(deg)), memset(vis, 0, sizeof(vis));
}

void ins(const struct node elem) {
	unsigned int n;
	for (heap[n = ++heap_size] = elem; heap[n >> 1].dist > elem.dist; n >>= 1) heap[n] = heap[n >> 1]; 
	heap[n] = elem;
}

struct node del_min(void) {
	unsigned int c, n;
	struct node min = heap[1], last = heap[heap_size--];
	for (n = 1; (n << 1) <= heap_size; n = c) {
		if (heap_size != (c = n << 1) && heap[c + 1].dist < heap[c].dist) ++c;
		if (last.dist > heap[c].dist) heap[n] = heap[c]; else break;
	}
	heap[n] = last;
	return min;
}

int main(int argc, char *argv[]) {
	int alt;
	unsigned int i, V, E, a, b, l, t, r;
	struct node heap_elem, min;
	init();
	scanf("%u%u", &V, &E);
	for (i = 0; i < E; ++i) scanf("%u%u%u", &a, &b, &l), --a, --b, G[a][deg[a]] = b, L[a][deg[a]] = l, ++deg[a], G[b][deg[b]] = a, L[b][deg[b]] = l, ++deg[b];
	ins((heap_elem.v = 0, heap_elem.dist = 0, heap_elem));
	for (alt = INF, dist[0][0] = 0, dist[0][1] = INF, i = 1; i < V; ++i) ins((heap_elem.v = i, heap_elem.dist = INF, heap_elem)), dist[i][0] = INF, dist[i][1] = INF;
	while (heap_size) {
		min = del_min();
		if ((r = vis[min.v]++) >= 2) continue;
		for (i = 0; i < deg[min.v]; ++i) if (dist[t = G[min.v][i]][0] > (alt = dist[min.v][r] + L[min.v][i])) dist[t][1] = dist[t][0], dist[t][0] = alt, ins((heap_elem.v = t, heap_elem.dist = alt, heap_elem)); else if (dist[t][1] > alt) dist[t][1] = alt, ins((heap_elem.v = t, heap_elem.dist = alt, heap_elem));
	}
	printf("%d\n", dist[V - 1][1]);
	return 0;
}
