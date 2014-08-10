#include <stdio.h>

#define MAX_N 100000

struct end_pt {
	unsigned long v, w;
	struct end_pt *next;
};

struct nd {
	struct nd *c[2];
};

unsigned int k, b, N, n, u, v, w, x, qfront, qback, num_nd, max, vis[MAX_N], xor_val[MAX_N], q[MAX_N];
struct end_pt e[MAX_N << 1], *ptr, *adj[MAX_N];
struct nd t[MAX_N << 5], *p;

struct nd * init(unsigned int *num_nd, struct nd t[]) {
	t[*num_nd].c[0] = NULL, t[*num_nd].c[1] = NULL;
	return &t[(*num_nd)++];
}

int main(int argc, char *argv[]) {
	while (EOF != scanf("%u", &N)) {
		for (n = 0; n < N; ++n) adj[n] = NULL, vis[n] = 0;
		for (n = 0; n + 1 < N; ++n) scanf("%u%u%u", &u, &v, &w), e[n << 1].v = v, e[n << 1].w = w, e[n << 1].next = adj[u], adj[u] = &e[n << 1], e[(n << 1) | 1].v = u, e[(n << 1) | 1].w = w, e[(n << 1) | 1].next = adj[v], adj[v] = &e[(n << 1) | 1];  
		for (qfront = 0, qback = 1, xor_val[0] = 0, q[0] = 0; qfront < qback; ) {
			vis[u = q[qfront++]] = 1;
			for (ptr = adj[u]; ptr; ptr = ptr -> next) if (!vis[ptr -> v]) xor_val[ptr -> v] = xor_val[u] ^ ptr -> w, q[qback++] = ptr -> v;
		}
		t[0].c[0] = NULL, t[0].c[1] = NULL;
		for (num_nd = 1, n = 0; n < N; ++n) {
			for (p = &t[0], k = 32; k; --k) {
				if (b = ((xor_val[n] >> (k - 1)) & 1), !p -> c[b]) p -> c[b] = init(&num_nd, t);
				p = p -> c[b];
			}
		}
		for (max = 0, n = 0; n < N; ++n) {
			for (x = 0, p = &t[0], k = 32; k; --k) if (p -> c[!(b = (xor_val[n] >> (k - 1)) & 1)]) x |= 1 << (k - 1), p = p -> c[!b]; else p = p -> c[b]; 
			if (x > max) max = x;
		}
		printf("%u\n", max);
	}
	return 0;
}
