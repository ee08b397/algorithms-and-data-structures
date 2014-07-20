#include <stdio.h>

#define MAX_N 1000000

unsigned int heap_size[2], N;
struct req {
	unsigned int key, priority, idx[2];
} reqs[MAX_N], *H[2][MAX_N + 1];

void push(struct req *const elem) {
	unsigned int p, q, s;
	struct req *tmp;
	for (s = 0; s < 2; ++s) for (H[s][p = ++heap_size[s]] = elem, q = p >> 1; q; p >>= 1, q >>= 1) if (s ? H[s][q] -> priority < H[s][p] -> priority : H[s][q] -> priority > H[s][p] -> priority) tmp = H[s][p], H[s][p] = H[s][q], H[s][q] = tmp, H[s][p] -> idx[s] = p, H[s][q] -> idx[s] = q; else { elem -> idx[s] = p; break; } 
}

struct req *pop(const int s) {
	unsigned int p, q, u; 
	struct req *tmp, *r;
	for (r = H[s][1], H[s][1] = H[s][heap_size[s]--], p = 1, q = 2; q <= heap_size[s]; q = p << 1) {
		if (s ? H[s][p] -> priority >= H[s][q] -> priority && ((q | 1) > heap_size[s] || H[s][p] -> priority >= H[s][q | 1] -> priority) : H[s][p] -> priority <= H[s][q] -> priority && ((q | 1) > heap_size[s] || H[s][p] -> priority <= H[s][q | 1] -> priority)) break;
		tmp = H[s][u = ((q | 1) > heap_size[s] ? q : ((s ? H[s][q] -> priority > H[s][q | 1] -> priority : H[s][q] -> priority < H[s][q | 1] -> priority) ? q : q | 1))], H[s][u] = H[s][p], H[s][p] = tmp, H[s][p] -> idx[s] = p, H[s][u] -> idx[s] = u, p = u; 
	}
	return r;
}

struct req *del(const int s, const unsigned int idx) {
	unsigned int p, q;
	for (p = idx, q = p >> 1; q; p >>= 1, q >>= 1) H[s][p] = H[s][q], H[s][p] -> idx[s] = p;
	return pop(s);
}

int main(int argc, char *argv[]) {
	unsigned int op, num_req;
	struct req *current_req;
	num_req = 0;
	while (EOF != scanf("%u", &op) && op) if (1 == op) scanf("%u%u", &reqs[num_req].key, &reqs[num_req].priority), push(&reqs[num_req]), ++num_req; else printf("%u\n", !heap_size[3 - op] ? 0 : (current_req = pop(3 - op), del(op - 2, current_req -> idx[op - 2]), current_req -> key));
	return 0;
}
