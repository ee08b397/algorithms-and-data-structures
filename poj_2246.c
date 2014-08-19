#include <stdio.h>

#define MAX_N 26
#define MAX_EXPR_LEN 127

char expr[MAX_EXPR_LEN + 1];
unsigned int offset, has_error;
unsigned long long eval, dim[MAX_N][2];

void parse_expr(unsigned long long *const r, unsigned long long *const c) {
	unsigned int idx; 
	unsigned long long r0, c0, r1, c1;
	if (has_error || !expr[offset]) return;
	if ('(' == expr[offset]) {
		++offset, parse_expr(&r0, &c0); if (has_error) return;
		++offset, parse_expr(&r1, &c1), ++offset; if (has_error) return;
		if (c0 != r1) { has_error = 1; return; }
		eval += r0 * c0 * c1, *r = r0, *c = c1;
		return;
	} 
	idx = expr[offset] - 'A', *r = dim[idx][0], *c = dim[idx][1];
}

int main(int argc, char *argv[]) {
	char matrix[2]; 
	unsigned int N, n;
	unsigned long long r, c;
	scanf("%u", &N);
	for (n = 0; n < N; ++n) scanf("%s%llu%llu", matrix, &r, &c), dim[matrix[0] - 'A'][0] = r, dim[matrix[0] - 'A'][1] = c;
	while (EOF != scanf("%s", expr)) {
		offset = 0, eval = 0, has_error = 0, parse_expr(&r, &c); 
		if (has_error) printf("error\n"); else printf("%llu\n", eval);
	}
	return 0;
}
