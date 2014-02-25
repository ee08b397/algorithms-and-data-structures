#include <stdio.h>

#define MAX_N 100

int main(int argc, char *argv[]) {
	unsigned long i, j, N, max, m[MAX_N][2];
	scanf("%lu", &N);
	scanf("%lu", &m[0][0]);
	for (i = 1; i < N; ++i) {
		scanf("%lu", &m[0][i & 1]);  
		m[0][i & 1] += m[0][~i & 1];
		for (j = 1; j < i; ++j) {
			scanf("%lu", &m[j][i & 1]);  
			m[j][i & 1] += m[j][~i & 1] > m[j - 1][~i & 1] ? m[j][~i & 1] : m[j - 1][~i & 1];
		}
		scanf("%lu", &m[i][i & 1]);  
		m[i][i & 1] += m[i - 1][~i & 1];
	}
	max = m[0][~N & 1];
	for (j = 0; j < N; ++j) {
		if (m[j][~N & 1] > max) {
			max = m[j][~N & 1];
		}
	}
	printf("%lu\n", max);
	return 0;
}
