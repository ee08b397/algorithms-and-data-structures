#include <stdio.h>

#define MAX_N 32

int main(int argc, char *argv[]) {
	int n, a, b, num_zero, case_num = 0, num_node, is_tree, node[MAX_N], deg[MAX_N];
	while (1) {
		for (n = 0; n < MAX_N; ++n) {
			deg[n] = 0;
			node[n] = 0;
		}
		is_tree = 1;
		++case_num;
		while (1) {
			scanf("%u %u", &a, &b);
			if (!a && !b) break;
			if (a < 0 && b < 0) return 0;
			node[a] = 1;
			node[b] = 1;
			++deg[b];
			if (deg[b] > 1) is_tree = 0;
		}
		num_zero = 0;
		num_node = 0;
		for (n = 0; n < MAX_N; ++n) {
			if (node[n]) {
				++num_node;
				if (!deg[n]) {
					if (++num_zero > 1) {
						is_tree = 0;
						break;
					}
				}
			}
		}
		if (num_node && !num_zero) is_tree = 0;
		printf("Case %d %s\n", case_num, is_tree ? "is a tree." : "is not a tree.");
	}
	return 0;
}
