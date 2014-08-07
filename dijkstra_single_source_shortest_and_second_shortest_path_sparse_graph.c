#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_V 10010    /* max number of vertices */
#define MAX_E 10010  /* max number of directed edges */
#define INF 0x4FFFFFFFFFFFFFFFLL

struct vertex {
	size_t v;
	int64_t dist;
};

struct pt {
	size_t v;
	int64_t l;
	struct pt *next;
};

size_t V, E, ne, heap_size;
int64_t dist[MAX_V];
struct vertex heap[MAX_E];
struct pt pts[MAX_E], *adj[MAX_V];

void init(void) {
	ne = 0, heap_size = 0, heap[0].v = -1, heap[0].dist = -1, memset(adj, 0, sizeof(adj));
}

void ins(const struct vertex elem) {
	size_t n;
	for (heap[n = ++heap_size] = elem; heap[n >> 1].dist > elem.dist; n >>= 1) heap[n] = heap[n >> 1]; 
	heap[n] = elem;
}

struct vertex del_min(void) {
	size_t c, n;
	struct vertex min = heap[1], last = heap[heap_size--];
	for (n = 1; (n << 1) <= heap_size; n = c) {
		if (heap_size != (c = n << 1) && heap[c + 1].dist < heap[c].dist) ++c;
		if (last.dist > heap[c].dist) heap[n] = heap[c]; else break;
	}
	heap[n] = last;
	return min;
}

int main(int argc, char *argv[]) {
	unsigned int T;
	size_t i, V, E, a, b, A, B, w;
	int64_t l, alt;
	struct vertex heap_elem, min;
	const struct pt *ptr;
	scanf("%u", &T);
	while (T--) {
		init();
		scanf("%zu%zu", &V, &E);
		for (i = 0; i < E; ++i) scanf("%zu%zu%ld", &a, &b, &l), pts[ne].v = b, pts[ne].l = l, pts[ne].next = adj[a], adj[a] = &pts[ne++], dist[a] = INF, dist[b] = INF;
		scanf("%zu%zu", &A, &B), dist[A] = 0, dist[B] = INF;
		ins((heap_elem.v = A, heap_elem.dist = 0, heap_elem));
		while (heap_size) {
			min = del_min();
			for (ptr = adj[min.v]; ptr; ptr = ptr -> next) if ((alt = dist[min.v] + ptr -> l) < dist[w = ptr -> v]) dist[w] = alt, ins((heap_elem.v = w, heap_elem.dist = alt, heap_elem));
		}
		if (INF == dist[B]) printf("NO\n"); else printf("%ld\n", dist[B]);
	}
	return 0;
}
