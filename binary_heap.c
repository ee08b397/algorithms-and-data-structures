#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define NUM_TEST 512
#define MAX_N 1024

size_t heap_size;
long K[MAX_N << 1];

struct elem {
	unsigned int value;
	long key;
	size_t pos;
} e[MAX_N + 1];

struct elem *heap[MAX_N + 1];

int cmp(const void *const a, const void *const b) {
	return *((const long *const)a) < *((const long *const)b) ? -1 : 1;
}

void init(void) {
	heap_size = 0, e[0].key = LONG_MIN, e[0].value = -1, heap[0] = &e[0];
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

void update_key(struct elem *const p, const long key) {
	long old_key;
	old_key = p->key, p->key = key;
	if (key < old_key) up(p); else down(p);
}

struct elem * del_min(void) {
	struct elem *min;
	min = heap[1], heap[1] = heap[heap_size--], heap[1]->pos = 1, down(heap[1]);
	return min;
}

int main(int argc, char *argv[]) {
	unsigned int n, T;
	FILE *fp;
	for (fp = fopen("/dev/urandom", "rb"), T = NUM_TEST; T; T--) {
		init();
		fread(K, sizeof(long), MAX_N << 1, fp);
		for (n = 0; n < MAX_N; ++n) e[n + 1].key = K[n], e[n + 1].value = n, ins(&e[n + 1]);
		qsort(K, MAX_N, sizeof(long), cmp); 
		for (n = 0; n < MAX_N; ++n) assert(K[n] == del_min()->key);
		for (n = 0; n < MAX_N; ++n) e[n + 1].key = K[n], e[n + 1].value = n, ins(&e[n + 1]);
		if (T & 1) for (n = 0; n < MAX_N; ++n) update_key(&e[n + 1], K[MAX_N + n]); else for (n = MAX_N; n; --n) update_key(&e[n], K[MAX_N + n - 1]);
		qsort(K + MAX_N, MAX_N, sizeof(long), cmp); 
		for (n = 0; n < MAX_N; ++n) assert(K[MAX_N + n] == del_min()->key);
	}
	fclose(fp);
	return 0;
}
