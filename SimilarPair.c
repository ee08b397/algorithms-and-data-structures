/* https://www.hackerrank.com/challenges/similarpair */

#include <stdio.h>
#include <string.h>

#define MAX_N 100000

struct edge {
	unsigned int e;
	struct edge *next;
} E[MAX_N], *s[MAX_N];

int seg[MAX_N << 1];
unsigned int N, T, P[MAX_N], Q[MAX_N], path[MAX_N];
unsigned long long ans;

int query(const size_t idx) {
	int val;
	size_t n;
	for (val = 0, n = idx + 1; n; n -= n & -n) val += seg[n - 1]; 
	return val;
}

void update(const size_t range_min, const size_t range_max, const int d) {
	size_t n;
	for (n = range_min + 1; n <= N; n += n & -n) seg[n - 1] += d;
	for (n = range_max + 2; n <= N; n += n & -n) seg[n - 1] -= d;
}

void ins_edge(const unsigned int n, const unsigned int a, const unsigned int b) {
	E[n].e = b, E[n].next = s[a], s[a] = &E[n];
}

void preorder_traversal(const unsigned int u) {
	unsigned int min, max;
	struct edge *ptr;
	ans += query(u);
	min = (u > T ? u - T : 0), max = (u + T < N ? u + T : N - 1);
	update(min, max, 1);
	for (ptr = s[u]; ptr; ptr = ptr->next) preorder_traversal(ptr->e);
	update(min, max, -1);
}

int main(int argc, char *argv[]) {
	unsigned int n, a, b;
	scanf("%u%u", &N, &T);
	for (n = 0; n < N; ++n) s[n] = NULL, P[n] = -1;
	memset(seg, 0, (N + 1) * sizeof(int));
	for (n = 0; n + 1 < N; ++n) scanf("%u%u", &a, &b), --a, --b, ins_edge(n, a, b), P[b] = a; 
	for (ans = 0, n = 0; n < N; ++n) if (-1 == P[n]) { preorder_traversal(n); break; }
	printf("%llu\n", ans);
	return 0;
}
