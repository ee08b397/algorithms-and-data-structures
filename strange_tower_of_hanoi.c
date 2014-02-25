#include <stdio.h>

#define N 12

int main(int argc, char *argv[]) {
	unsigned int n, k, min, alt, num_move[N]; 
	num_move[0] = 1;
	printf("1\n");
	for (n = 1; n < N; ++n) {
		min = (1 << (n + 1)) - 1;
		for (k = 0; k < n; ++k) if ((alt = (num_move[k] << 1) + (1 << (n - k)) - 1) < min) min = alt;
		printf("%u\n", num_move[n] = min);
	}
	return 0;
}
