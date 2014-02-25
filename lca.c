#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TREE_SIZE 900

void skip_whitespace(void) {
	char w;
	while (scanf("%c", &w) != EOF) {
		if (!isspace(w)) {
			ungetc(w, stdin);
			return;
		}
	}
}

int main(int argc, char *argv[]) {
	char w;
	unsigned int l, n, nc, c, s, a, b, pa, pb, na, nb, num_test, tree_size;
	unsigned int parent[MAX_TREE_SIZE];
	unsigned int path_a[MAX_TREE_SIZE];
	unsigned int path_b[MAX_TREE_SIZE];
	unsigned int lca_freq[MAX_TREE_SIZE];
	memset(parent, 0, sizeof(unsigned int) * MAX_TREE_SIZE);
	memset(lca_freq, 0, sizeof(unsigned int) * MAX_TREE_SIZE);
	scanf("%u%c", &tree_size, &w);
	for (l = 0; l < tree_size; ++l) {
		scanf("%u:(%u)", &n, &nc);
		for (c = 0; c < nc; ++c) {
			skip_whitespace();
			scanf("%u", &s);
			parent[s - 1] = n;
		}
	}
	scanf("%u", &num_test); 
	skip_whitespace();
	for (l = 0; l < num_test; ++l) {
		unsigned int lca = -1; 
		scanf("(%u", &a);
		skip_whitespace();
		scanf("%u)", &b);  
		skip_whitespace();
		pa = 0;
		pb = 0;
		na = a;
		nb = b;
		while (1) {
			path_a[pa++] = na;
			if (parent[na - 1] == 0) {
				break;
			}
			na = parent[na - 1];
		}
		while (1) {
			path_b[pb++] = nb;
			if (parent[nb - 1] == 0) {
				break;
			}
			nb = parent[nb - 1]; 
		}
		while (pa > 0 && pb > 0 && path_a[--pa] == path_b[--pb]) {
			lca = path_a[pa];
		}
		++lca_freq[lca - 1];
	}
	for (l = 0; l < MAX_TREE_SIZE; ++l) {
		if (lca_freq[l]) {
			printf("%u:%u\n", l + 1, lca_freq[l]);
		}
	}
	return 0;	
}
