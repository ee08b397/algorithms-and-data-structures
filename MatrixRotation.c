#include <stdio.h>

#define MAX_LEN 300

unsigned int M, N, R, len[MAX_LEN >> 1], src[MAX_LEN][MAX_LEN], dest[MAX_LEN][MAX_LEN], coord[MAX_LEN >> 1][MAX_LEN << 2][2];

int main(int argc, char *argv[]) {
	unsigned int i, j, k, kd, l, L;
	scanf("%u%u%u", &M, &N, &R), L = ((M < N ? M : N) >> 1);
	for (i = 0; i < M; ++i) for (j = 0; j < N; ++j) scanf("%u", &src[i][j]);
	for (l = 0; l < L; ++l) {
		k = 0, len[l] = ((M + N) << 1) - (l << 3) - 4;
		for (i = l; i + l + 1 < M; ++i, ++k) coord[l][k][0] = i, coord[l][k][1] = l;
		for (j = l; j + l + 1 < N; ++j, ++k) coord[l][k][0] = M - l - 1, coord[l][k][1] = j;
		for (i = M - l - 1; i > l; --i, ++k) coord[l][k][0] = i, coord[l][k][1] = N - l - 1;  
		for (j = N - l - 1; j > l; --j, ++k) coord[l][k][0] = l, coord[l][k][1] = j; 
	}
	for (l = 0; l < L; ++l) for (k = 0; k < len[l]; ++k) kd = (k + R) % len[l], dest[coord[l][kd][0]][coord[l][kd][1]] = src[coord[l][k][0]][coord[l][k][1]];
	for (i = 0; i < M; ++i) for (j = 0; j < N; ++j) printf("%u%c", dest[i][j], N == j + 1 ? '\n' : ' ');
	return 0;
}
