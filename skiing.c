#include <stdio.h>

#define MAX_N 100
#define MAX_H 10000

unsigned int max_len(const unsigned int R, const unsigned int C, const unsigned int r, const unsigned int c, const unsigned int h[][MAX_N], unsigned int mem[][MAX_N]) {
	if (mem[r][c] < MAX_H + 1) return mem[r][c];
	unsigned int max_l = 1, l, ch = h[r][c];
	if (r && h[r - 1][c] < ch && (l = 1 + max_len(R, C, r - 1, c, h, mem)) > max_l) max_l = l;
	if (r + 1 < R && h[r + 1][c] < ch && (l = 1 + max_len(R, C, r + 1, c, h, mem)) > max_l) max_l = l;
	if (c && h[r][c - 1] < ch && (l = 1 + max_len(R, C, r, c - 1, h, mem)) > max_l) max_l = l;
	if (c + 1 < C && h[r][c + 1] < ch && (l = 1 + max_len(R, C, r, c + 1, h, mem)) > max_l) max_l = l;
	return mem[r][c] = max_l;
}

int main(int argc, char *argv[]) {
	unsigned int R, C, r, c, l, max_l = 0, h[MAX_N][MAX_N], mem[MAX_N][MAX_N];
	scanf("%u%u", &R, &C);
	for (r = 0; r < R; ++r) for (c = 0; c < C; ++c) { scanf("%u", &h[r][c]); mem[r][c] = MAX_H + 1; }
	for (r = 0; r < R; ++r) for (c = 0; c < C; ++c) if ((l = max_len(R, C, r, c, (const unsigned int(*)[MAX_N])h, mem)) > max_l) max_l = l;
	printf("%u\n", max_l);
	return 0;
}
