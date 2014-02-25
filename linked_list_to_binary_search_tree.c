#include <stdio.h>

#define N 32

typedef struct binary_tree_node {
	int value;
	struct binary_tree_node *left, *right;
} binary_tree_node;

binary_tree_node *linkedlist_to_binary_tree(const size_t start, const size_t end, size_t *bn_idx, const int n[], binary_tree_node bn[]) {
	size_t idx = (*bn_idx)++, mid;
	if (start == end) {
		bn[idx].value = n[end];
		bn[idx].left = NULL;
		bn[idx].right = NULL;
		return &bn[idx];
	}
	mid = (start + end) >> 1;
	bn[idx].left = start + 1 <= mid ? linkedlist_to_binary_tree(start, mid - 1, bn_idx, n, bn) : NULL;
	bn[idx].value = n[mid];
	bn[idx].right = mid + 1 <= end ? linkedlist_to_binary_tree(mid + 1, end, bn_idx, n, bn) : NULL;
	return &bn[idx];
}

void print_binary_tree(const binary_tree_node *root) {
	if (root) {
		printf("(");
		print_binary_tree(root -> left);
		printf("%d", root -> value); 
		print_binary_tree(root -> right);
		printf(")");
	}
}

int main(int argc, char *argv[]) {
	size_t k, bn_idx;
	int n[N];
	binary_tree_node bn[N], *root;
	for (k = 0; k < N; ++k) {
		n[k] = k + 1;
	}
	bn_idx = 0;
	root = linkedlist_to_binary_tree(0, N - 1, &bn_idx, n, bn);
	print_binary_tree(root);
	printf("\n");
	return 0;
}
