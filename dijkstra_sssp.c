#include <stdio.h>
#include <string.h>

#define MAX_V 10001   /* max number of vertices */
#define MAX_E 10001  /* max number of directed edges */
#define INF 0x4FFFFFFF

struct node {
	unsigned int v;
	int dist;
};

unsigned int V, E, heap_size, deg[MAX_V], vis[MAX_V], G[MAX_V][MAX_V];
int dist[MAX_V], L[MAX_V][MAX_V];
struct node heap[MAX_E];

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
	unsigned int i, T, V, E, src, dest, a, b, l, t;
	struct node heap_elem, min;
	scanf("%u", &T);
	while (T--) {
		init();
		scanf("%u%u", &V, &E);
		for (i = 0; i < E; ++i) scanf("%u%u%u", &a, &b, &l), --a, --b, G[a][deg[a]] = b, L[a][deg[a]] = l, ++deg[a], G[b][deg[b]] = a, L[b][deg[b]] = l, ++deg[b];
		scanf("%u%u", &src, &dest), --src, --dest;
		for (i = 0; i < V; ++i) ins((heap_elem.v = i, dist[i] = heap_elem.dist = (src == i ? 0 : INF), heap_elem));
		while (heap_size) {
			min = del_min();
			if (vis[min.v]) continue;
			for (vis[min.v] = 1, i = 0; i < deg[min.v]; ++i) if (dist[t = G[min.v][i]] > (alt = dist[min.v] + L[min.v][i])) ins((heap_elem.v = t, dist[t] = heap_elem.dist = alt, heap_elem));
		}
		if (INF == dist[dest]) printf("NO\n"); else printf("%d\n", dist[dest]);
	}
	return 0;
}
