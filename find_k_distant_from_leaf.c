#include <stdio.h>

struct node {
	unsigned int key;
	struct node *left, *right;
};

unsigned int find_k_distant_from_leaf(const unsigned int k, const struct node *const root) {
	int h_l, h_r, printed = 0; 
	if (root) {
		if ((h_l = find_k_distant_from_leaf(k, root -> left)) + 1 == k) printf("%u ", root -> key), printed = 1;
		if ((h_r = find_k_distant_from_leaf(k, root -> right)) + 1 == k) if (!printed) printf("%u ", root -> key);
		return (h_l > h_r ? h_l : h_r) + 1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	unsigned int i;
	struct node t[8];
	for (i = 0; i < 8; ++i) t[i].key = i + 1;  
	t[0].left = &t[1]; 
	t[0].right = &t[2]; 
	t[1].left = &t[3]; 
	t[1].right = &t[4]; 
	t[2].left = &t[5];
	t[2].right = &t[6];
	t[3].right = t[3].left = NULL;
	t[4].right = t[4].left = NULL;
	t[5].left = NULL;
	t[5].right = &t[7];
	t[6].right = t[6].left = NULL;
	t[7].right = t[7].left = NULL;
	find_k_distant_from_leaf(4, &t[0]);
	printf("\n");
	find_k_distant_from_leaf(3, &t[0]);
	printf("\n");
	find_k_distant_from_leaf(2, &t[0]);
	printf("\n");
	find_k_distant_from_leaf(1, &t[0]);
	printf("\n");
	return 0;
}
