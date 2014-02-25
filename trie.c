#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define CHAR_SET_SIZE 56
#define MAX_WORD_LEN 60
#define MAX_NUM_WORD 1000

typedef struct node {
	unsigned short next[CHAR_SET_SIZE];
} node;

unsigned short tok(const char c) {
	return c >= 'A' && c <= 'Z' ? c - 'A' : c >= 'a' && c <= 'z' ? c - 'a' + 26 : c == '.' ? 52 : c == ',' ? 53 : c == '?' ? 54 : 55;
}

void init_node(const size_t idx, node *const pn) {
	unsigned int i;
	for (i = 0; i < CHAR_SET_SIZE; ++i) pn[idx].next[i] = USHRT_MAX;
}

int main(int argc, char *argv[]) {
	unsigned short M, N, m, n, t, num_node = 1, is_prefix, num_prefix;
	char c;
	node *pn = (node *)malloc((1 + MAX_WORD_LEN * MAX_NUM_WORD) * sizeof(node)), *ptr;
	init_node(0, pn);
	scanf("%hu%hu", &M, &N);
	getc(stdin);
	for (m = 0; m < M; ++m) {
		ptr = &pn[0];
		while ((c = getc(stdin)) != '\n') {
			t = tok(c);
			if (ptr -> next[t] == USHRT_MAX) { init_node(num_node, pn); ptr -> next[t] = num_node; ptr = &pn[num_node++]; } else ptr = &pn[ptr -> next[t]];
		}
	}
	for (num_prefix = 0, n = 0; n < N; ++n) {
		ptr = &pn[0];
		is_prefix = 1;
		while ((c = getc(stdin)) != '\n') {
			if (!is_prefix) continue;
			t = tok(c);
			if (ptr -> next[t] == USHRT_MAX) is_prefix = 0; else ptr = &pn[ptr -> next[t]];
		}
		if (is_prefix) ++num_prefix;
	}
	printf("%hu\n", num_prefix);
	free(pn);
	return 0;
}
