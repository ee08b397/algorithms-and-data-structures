#include <stdio.h>
#include <limits.h>

#define MAX_N 1000
#define MAX_M 15000

size_t heap_size;
int conn[MAX_N];
unsigned int plan[MAX_M][2];

struct elem {
	unsigned int u, v;
	long key;
	size_t pos;
} V[MAX_N + 1];

struct end_pt {
	unsigned int v, L;
	struct end_pt *next;
} E[MAX_M << 1];

struct elem *heap[MAX_N + 1];
struct end_pt *adj[MAX_N];

void init(void) {
	heap_size = 0, V[MAX_N].key = LONG_MIN, heap[0] = &V[MAX_N];
}

void up(struct elem *const p) {
	size_t n;
	for (n = p->pos; heap[n >> 1]->key > p->key; n >>= 1) heap[n] = heap[n >> 1], heap[n]->pos = n;
	heap[n] = p, p->pos = n;
}

void down(struct elem *const p) {
	size_t n, d, c;
	for (n = p->pos; (d = n << 1) <= heap_size; n = c) if (p->key > heap[c = ((d < heap_size && heap[d + 1]->key < heap[d]->key) ? d + 1 : d)]->key) heap[n] = heap[c], heap[n]->pos = n; else break;
	heap[n] = p, p->pos = n; 
}

void ins(struct elem *const p) {
	up(heap[p->pos = ++heap_size] = p);
}

struct elem * del_min(void) {
	struct elem *min;
	min = heap[1], heap[1] = heap[heap_size--], heap[1]->pos = 1, down(heap[1]);
	return min;
}

int main(int argc, char *argv[]) {
	unsigned int N, M, n, m, u, v, L, max_L, num_cable;
	struct elem *vptr;
	struct end_pt *eptr;
	while (EOF != scanf("%u%u", &N, &M)) {
		init();
		for (n = 0; n < N; ++n) conn[n] = 0, adj[n] = NULL;
		V[0].v = 0, V[0].key = 0, ins(&V[0]);
		for (n = 1; n < N; ++n) V[n].v = n, V[n].key = LONG_MAX, ins(&V[n]);
		for (m = 0; m < M; ++m) scanf("%u%u%u", &u, &v, &L), --u, --v, E[m << 1].v = v, E[m << 1].L = L, E[m << 1].next = adj[u], adj[u] = &E[m << 1], E[(m << 1) | 1].v = u, E[(m << 1) | 1].L = L, E[(m << 1) | 1].next = adj[v], adj[v] = &E[(m << 1) | 1];
		max_L = 0, num_cable = 0;
		while (heap_size) {
			vptr = del_min(), u = vptr->u, v = vptr->v, conn[v] = 1;
			if (v) {
				plan[num_cable][0] = u, plan[num_cable][1] = v, ++num_cable;
				if (vptr->key > max_L) max_L = vptr->key; 
			}
			for (eptr = adj[v]; eptr; eptr = eptr->next) if (!conn[eptr->v] && V[eptr->v].key > eptr->L) V[eptr->v].key = eptr->L, V[eptr->v].u = v, up(&V[eptr->v]);
		}
		printf("%u\n%u\n", max_L, N - 1);
		for (n = 0; n + 1 < N; ++n) printf("%u %u\n", plan[n][0] + 1, plan[n][1] + 1);
	}
	return 0;
}
