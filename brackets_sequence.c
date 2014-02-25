#include <stdio.h>
#include <string.h>
#include <limits.h>

#define LPAREN '('
#define RPAREN ')'
#define LBRACKET '['
#define RBRACKET ']'
#define MAX_INPUT_LEN 100

unsigned int compute_min_num_ins(const char input[], const unsigned int start, const unsigned int end, unsigned int mem[][MAX_INPUT_LEN], unsigned int optimal_k[][MAX_INPUT_LEN]) {
	unsigned int k, alt;
	if (start > end) return 0;
	if (mem[start - 1][end - 1] != UINT_MAX) return mem[start - 1][end - 1];
	if ((input[start - 1] == LPAREN && input[end - 1] == RPAREN) || (input[start - 1] == LBRACKET && input[end - 1] == RBRACKET)) { mem[start - 1][end - 1] = compute_min_num_ins(input, start + 1, end - 1, mem, optimal_k); optimal_k[start - 1][end - 1] = UINT_MAX; }
	for (k = start; k <= end; ++k) if ((alt = compute_min_num_ins(input, start, k, mem, optimal_k) + compute_min_num_ins(input, k + 1, end, mem, optimal_k)) < mem[start - 1][end - 1]) { mem[start - 1][end - 1] = alt; optimal_k[start - 1][end - 1] = k; } 
	return mem[start - 1][end - 1];
}

void print_seq(const char input[], const unsigned int start, const unsigned int end, const unsigned int optimal_k[][MAX_INPUT_LEN]) {
	if (start > end) return;
	if (start == end) {
		if (input[start - 1] == LPAREN || input[start - 1] == RPAREN) {
			putc(LPAREN, stdout);
			putc(RPAREN, stdout);
		}else {
			putc(LBRACKET, stdout);
			putc(RBRACKET, stdout);
		}
	}else if (optimal_k[start - 1][end - 1] == UINT_MAX) {
		putc(input[start - 1], stdout);
		print_seq(input, start + 1, end - 1, optimal_k);
		putc(input[end - 1], stdout);
	}else {
		print_seq(input, start, optimal_k[start - 1][end - 1], optimal_k); 
		print_seq(input, optimal_k[start - 1][end - 1] + 1, end, optimal_k); 
	}
}

int main(int argc, char *argv[]) {
	char input[MAX_INPUT_LEN + 1];
	unsigned int length, i, j, mem[MAX_INPUT_LEN][MAX_INPUT_LEN], optimal_k[MAX_INPUT_LEN][MAX_INPUT_LEN];
	scanf("%s", input);
	length = strlen(input);
	for (i = 0; i < length; ++i) for (mem[i][i] = 1, j = i + 1; j < length; ++j) mem[i][j] = UINT_MAX;
	compute_min_num_ins(input, 1, length, mem, optimal_k);
	print_seq(input, 1, length, (const unsigned int(*)[MAX_INPUT_LEN])optimal_k);
	putc('\n', stdout);
	return 0;
}
