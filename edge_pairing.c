#include <stdio.h>

#define MAX_N 20000
#define MAX_M 100000
#define INF 0x0FFFFFFF

struct end_pt {
	unsigned int n;
	struct end_pt *next;
};

unsigned int dfs(const unsigned int root, const struct end_pt *adj[], unsigned int *const current_seq_num, unsigned int seq_num[]) {
	unsigned int current_end_pt = INF, chld_end_pt;
	const struct end_pt *ptr;
	seq_num[root] = (*current_seq_num)++;
	for (ptr = adj[root]; ptr; ptr = ptr -> next) {
		if (seq_num[ptr -> n] == INF && (chld_end_pt = dfs(ptr -> n, adj, current_seq_num, seq_num)) != INF) {
			printf("%u %u %u\n", chld_end_pt + 1, (ptr -> n) + 1, root + 1);
		}else if (seq_num[ptr -> n] > seq_num[root]) {
			if (current_end_pt != INF) { 
				printf("%u %u %u\n", current_end_pt + 1, root + 1, ptr -> n + 1);
				current_end_pt = INF;
			}else {
				current_end_pt = ptr -> n;
			}
		}
	}
	return current_end_pt;
}

int main(int argc, char *argv[]) {
	unsigned int N, M, m, n, a, b, current_seq_num = 0, seq_num[MAX_N];
	struct end_pt p[MAX_M << 1], *adj[MAX_N];
	scanf("%u%u", &N, &M);
	for (n = 0; n < N; ++n) adj[n] = NULL, seq_num[n] = INF;
	for (m = 0; m < M; ++m) {
		scanf("%u%u", &a, &b);
		--a;
		--b;
		p[m << 1].n = b;
		p[m << 1].next = adj[a];
		adj[a] = &p[m << 1];
		p[(m << 1) + 1].n = a;
		p[(m << 1) + 1].next = adj[b];
		adj[b] = &p[(m << 1) + 1];
	}
	/* printf("current_end_pt == %u\n", dfs(0, (const struct end_pt**)adj, &current_seq_num, seq_num)); */
	dfs(0, (const struct end_pt**)adj, &current_seq_num, seq_num);
	return 0;
}
