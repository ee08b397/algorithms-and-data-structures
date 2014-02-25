#include <stdio.h>
#include <limits.h>

#define A 0
#define T 1
#define C 2
#define G 3 

#define MAX_N 50
#define MAX_SEG_LEN 20
#define MAX_INPUT_LEN 1000

struct node {
	char is_disease;
	unsigned int num;
	struct node *next[4];
	struct node *fp;
};

int main(int argc, char *argv[]) {
	const unsigned int MAX_NUM_NODE = (MAX_SEG_LEN + 1) * MAX_N;
	unsigned int case_num, N, num_node, j, k, idx, ridx, qfront, qback, input_len, num_repair, min_num_repair, mem[MAX_INPUT_LEN + 1][MAX_NUM_NODE]; 
	char seg[MAX_SEG_LEN + 1], input[MAX_INPUT_LEN + 1];
	struct node n[MAX_NUM_NODE], *root, *ptr, *pf, *queue[MAX_NUM_NODE];
	case_num = 0;
	while (1) {
		scanf("%u", &N);
		if (!N) return 0;
		n[0].is_disease = 0;
		n[0].num = 0;
		n[0].next[A] = n[0].next[T] = n[0].next[C] = n[0].next[G] = NULL;
		n[0].fp = &n[0];
		root = &n[0];
		num_node = 1;
		/* trie construction */
		while (N--) {
			scanf("%s", seg);
			/* printf("seg == %s\n", seg); */
			for (k = 0, ptr = root; seg[k]; ++k) {
				idx = seg[k] == 'A' ? A : seg[k] == 'T' ? T : seg[k] == 'C' ? C : G; 
				if (!ptr -> next[idx]) {
					n[num_node].is_disease = 0;
					n[num_node].num = num_node;
					n[num_node].fp = n[num_node].next[A] = n[num_node].next[T] = n[num_node].next[C] = n[num_node].next[G] = NULL;
					ptr -> next[idx] = &n[num_node++];
				}
				ptr = ptr -> next[idx];
			}
			ptr -> is_disease = 1;
		}
		/* Aho-Corasick automaton construction */
		qfront = 0;
		qback = 0;
		for (k = 0; k < 4; ++k) {
			if (root -> next[k]) {
				queue[qback++] = root -> next[k];
				root -> next[k] -> fp = root;
			}else root -> next[k] = root;
		}
		while (qback > qfront) {
			/* printf("dequeue\n"); */
			ptr = queue[qfront++];
			for (k = 0; k < 4; ++k) {
				if (ptr -> next[k]) {
					/* printf("enqueue\n"); */
					queue[qback++] = ptr -> next[k];
					pf = ptr -> fp;
					while (!pf -> next[k]) pf = pf -> fp; 
					ptr -> next[k] -> is_disease |= (ptr -> next[k] -> fp = pf -> next[k]) -> is_disease;
				}
			}
		}
		scanf("%s", input);
		/* printf("input == %s\n", input); */
		for (k = 0; input[k]; ++k) {
			for (idx = 0; idx < num_node; ++idx) {
				mem[k + 1][idx] = UINT_MAX;
			}
		}
		input_len = k;
		for (idx = 1; idx < num_node; ++idx) {
			mem[0][idx] = UINT_MAX;
		}
		mem[0][0] = 0;
		for (k = 0; k < input_len; ++k) {
			idx = input[k] == 'A' ? A : input[k] == 'T' ? T : input[k] == 'C' ? C : G;
			for (j = 0; j < num_node; ++j) {   /* assuming previous state is state #j */
				if (mem[k][j] == UINT_MAX) continue;
				for (ridx = 0; ridx < 4; ++ridx) {
					ptr = &n[j];
					while (!ptr -> next[ridx]) ptr = ptr -> fp;
					ptr = ptr -> next[ridx];
					if (ptr -> is_disease) continue;
					if ((num_repair = mem[k][j] + (ridx == idx ? 0 : 1)) < mem[k + 1][ptr -> num]) {
						mem[k + 1][ptr -> num] = num_repair;
					}
				}
			}
		}
		min_num_repair = UINT_MAX;
		for (j = 0; j < num_node; ++j) if (mem[input_len][j] < min_num_repair) min_num_repair = mem[input_len][j];
		++case_num;
		printf("Case %u: ", case_num);
		if (min_num_repair == UINT_MAX) printf("-1\n"); else printf("%u\n", min_num_repair);
	}
	return 0;
}
