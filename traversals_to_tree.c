#include <stdio.h>

struct node {
	size_t idx;
	struct node *ptr_c;
	struct node *ptr_n;
};

void print_tree(const unsigned int level, const struct node *n_ptr) {
	unsigned int i;
	printf("|");
	for (i = 0; i < level; ++i) {
		printf("    |");
	}
	printf("\n|");
	for (i = 0; i < level; ++i) {
		printf("    |");
	}
	printf("____%zu\n", n_ptr -> idx);
	const struct node *nc = n_ptr -> ptr_c;
	while (nc) {
		print_tree(level + 1, nc);
		nc = nc -> ptr_n;
	}
}

void pre_order_traversal(size_t * const idx, const struct node *n_ptr, size_t result[]) {
	struct node *ptr_c = n_ptr -> ptr_c;
	struct node *ptr_n = n_ptr -> ptr_n;
	result[(*idx)++] = n_ptr -> idx;
	if (ptr_c) {
		pre_order_traversal(idx, ptr_c, result);
	}
	if (ptr_n) {
		pre_order_traversal(idx, ptr_n, result);
	}
}

void post_order_traversal(size_t * const idx, const struct node *n_ptr, size_t result[]) {
	struct node *ptr_c = n_ptr -> ptr_c;
	struct node *ptr_n = n_ptr -> ptr_n;
	if (ptr_c) {
		post_order_traversal(idx, ptr_c, result);
	}
	result[(*idx)++] = n_ptr -> idx;
	if (ptr_n) {
		post_order_traversal(idx, ptr_n, result);
	}
}

void traversals_to_tree(const size_t tree_size, const size_t pre_order_traversal[], const size_t post_order_traversal[], size_t *root_idx, struct node rt[]) {
	if (tree_size > 0) { 
		size_t i, j, prev_post_order_idx = tree_size - 1;
		struct node *prev_node;
		*root_idx = pre_order_traversal[0];
		prev_node = &rt[*root_idx];
		rt[*root_idx].ptr_c = NULL; 
		rt[*root_idx].ptr_n = NULL; 
		rt[*root_idx].idx = *root_idx;
		for (i = 1; i < tree_size; ++i) {
			size_t p_i = pre_order_traversal[i];
			for (j = 0; j < tree_size; ++j) {
				if (post_order_traversal[j] == p_i) {
					break;
				}
			}
			rt[p_i].ptr_c = NULL; 
			rt[p_i].ptr_n = NULL; 
			if (j < prev_post_order_idx) {
				prev_node -> ptr_c = &rt[p_i];
			}else {
				size_t k = j + 1;
				while (1) {
					int lca = 0;
					size_t l;
					for (l = i - 1; l > 0; --l) {
						if (pre_order_traversal[l] == post_order_traversal[k]) {
							lca = 1;
							break;
						}
					}
					if (lca) {
						break;
					}
					++k;
				}
				struct node *nn = rt[post_order_traversal[k]].ptr_c; 
				while (nn -> ptr_n) {
					nn = nn -> ptr_n;
				}
				nn -> ptr_n = &rt[p_i];
			}
			rt[p_i].idx = p_i; 
			prev_node = &rt[p_i];
			prev_post_order_idx = j;
		}
		/*
		for (i = 0; i < tree_size; ++i) {
			if (rt[i].ptr_c) {
				rt[i].ptr_c -> ptr_c = &rt[i];
			}
		}
		*/
	}
}

int main(int argc, char *argv[]) {
	unsigned int i;
	size_t pre_order_idx = 0, post_order_idx = 0, root_idx;
	size_t pre_order_result[13], post_order_result[13];
	struct node n[13], rt[13]; 
	for (i = 0; i < 13; ++i) {
		n[i].idx = i;
	}
	n[0].ptr_c = &n[1];
	n[0].ptr_n = NULL;
	n[1].ptr_c = &n[2];
	n[1].ptr_n = &n[3];
	n[2].ptr_c = NULL;
	n[2].ptr_n = &n[4];
	n[3].ptr_c = &n[9];
	n[3].ptr_n = NULL;
	n[4].ptr_c = &n[5];
	n[4].ptr_n = NULL;
	n[5].ptr_c = &n[6];
	n[5].ptr_n = &n[8];
	n[6].ptr_c = NULL;
	n[6].ptr_n = &n[7];
	n[7].ptr_c = NULL;
	n[7].ptr_n = NULL;
	n[8].ptr_c = NULL;
	n[8].ptr_n = NULL;
	n[9].ptr_c = &n[10];
	n[9].ptr_n = NULL;
	n[10].ptr_c = &n[11];
	n[10].ptr_n = &n[12];
	n[11].ptr_c = NULL;
	n[11].ptr_n = NULL;
	n[12].ptr_c = NULL;
	n[12].ptr_n = NULL;
	printf("T:\n");
	print_tree(0, &n[0]);
	pre_order_traversal(&pre_order_idx, &n[0], pre_order_result);
	printf("\npre-order traversal result:\n");
	for (i = 0; i < 13; ++i) {
		printf("%zu,", pre_order_result[i]);
	}
	printf("\n");
	post_order_traversal(&post_order_idx, &n[0], post_order_result);
	printf("\npost-order traversal result:\n");
	for (i = 0; i < 13; ++i) {
		printf("%zu,", post_order_result[i]);
	}
	printf("\n");
	traversals_to_tree(13, pre_order_result, post_order_result, &root_idx, rt);
	printf("reconstructed tree:\n");
	print_tree(0, &rt[root_idx]);
	return 0;
}
