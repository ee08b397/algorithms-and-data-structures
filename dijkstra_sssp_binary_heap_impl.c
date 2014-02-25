#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
//#define BIG_EXAMPLE
 
typedef struct node_t node_t, *heap_t;
typedef struct edge_t edge_t;

struct edge_t {
	node_t *nd;	/* target of this edge */
	edge_t *sibling;/* for singly linked list */
	int len;	/* edge cost */
};

struct node_t {
	edge_t *edge;	/* singly linked list of edges */
	node_t *via;	/* where previous node is in shortest path */
	double dist;	/* distance from origining node */
	char name[8];	/* the, er, name */
	int heap_idx;	/* link to heap position for updating distance */
};
 
 
/* --- edge management --- */
#define BLOCK_SIZE 4001

edge_t *edge_root = 0, *e_next = 0;
 
/* Don't mind the memory management stuff, they are besides the point.
   Pretend e_next = malloc(sizeof(edge_t)) */
void add_edge(node_t *const a, node_t *const b, double d) {
	if (e_next == edge_root) {
		edge_root = malloc(sizeof(edge_t) * (BLOCK_SIZE + 1));
		edge_root[BLOCK_SIZE].sibling = e_next;
		e_next = edge_root + BLOCK_SIZE;
	}
	--e_next;
	e_next -> nd = b;
	e_next -> len = d;
	e_next -> sibling = a -> edge;
	a -> edge = e_next;
}
 
void free_edges() {
	for (; edge_root; edge_root = e_next) {
		e_next = edge_root[BLOCK_SIZE].sibling;
		free(edge_root);
	}
}
 
/* --- priority queue stuff --- */
heap_t *heap;
int heap_len;
 
void set_dist(node_t * const nd, node_t *const via, double d) {
	int i, j;
 
	/* already knew better path */
	if (nd->via && d >= nd->dist) return;
 
	/* find existing heap entry, or create a new one */
	nd->dist = d;
	nd->via = via;
 
	i = nd->heap_idx;
	if (!i) i = ++heap_len;
 
	/* upheap */
	for (; i > 1 && nd->dist < heap[j = i/2]->dist; i = j)
		(heap[i] = heap[j])->heap_idx = i;
 
	heap[i] = nd;
	nd->heap_idx = i;
}
 
node_t * pop_queue() {
	node_t *nd, *tmp;
	int i, j;
 
	if (!heap_len) return 0;
 
	/* remove leading element, pull tail element there and downheap */
	nd = heap[1];
	tmp = heap[heap_len--];
 
	for (i = 1; i < heap_len && (j = i * 2) <= heap_len; i = j) {
		if (j < heap_len && heap[j]->dist > heap[j+1]->dist) j++;
 
		if (heap[j]->dist >= tmp->dist) break;
		(heap[i] = heap[j])->heap_idx = i;
	}
 
	heap[i] = tmp;
	tmp->heap_idx = i;
 
	return nd;
}
 
/* --- Dijkstra stuff; unreachable nodes will never make into the queue --- */
void calc_all(node_t *const start) {
	node_t *lead;
	edge_t *e;
 
	set_dist(start, start, 0);
	while ((lead = pop_queue()))
		for (e = lead->edge; e; e = e->sibling)
			set_dist(e->nd, lead, lead->dist + e->len);
}
 
void show_path(node_t *const nd) {
	if (nd->via == nd)
		printf("%s", nd->name);
	else if (!nd->via)
		printf("%s(unreached)", nd->name);
	else {
		show_path(nd->via);
		printf("-> %s(%g) ", nd->name, nd->dist);
	}
}
 
int main(int argc, char *argv[]) {
	unsigned int T, N, t, a, b, l;
	scanf("%u%u", &T, &N);
	node_t *nodes = calloc(sizeof(node_t), N);
	for (t = 0; t < T; ++t) {
		scanf("%u%u%u", &a, &b, &l);
		--a;
		--b;
		add_edge(nodes + a, nodes + b, l);
		add_edge(nodes + b, nodes + a, l);
	}
	heap = calloc(sizeof(heap_t), N);
	heap_len = 0;
 
	calc_all(nodes);
	for (i = 0; i < N; i++) {
		show_path(nodes + i);
		putchar('\n');
	}
	free_edges();
	free(heap);
	free(nodes);
	return 0;
}
