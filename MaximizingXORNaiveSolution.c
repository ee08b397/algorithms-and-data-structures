#include <stdio.h>

int main(int argc, char *argv[]) {
	unsigned int max, L, R, A, B, x;
	scanf("%u%u", &L, &R);
	for (max = 0, A = L; A <= R; ++A) for (B = A + 1; B <= R; ++B) if ((x = A ^ B) > max) max = x; 
	printf("%u\n", max);
	return 0;
}
