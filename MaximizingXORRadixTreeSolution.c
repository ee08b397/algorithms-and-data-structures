#include <stdio.h>

#define MAX_N 1000

struct nd {
	struct nd *c[2];
};

struct nd * init(unsigned int *num_nd, struct nd t[]) {
	t[*num_nd].c[0] = NULL, t[*num_nd].c[1] = NULL;
	return &t[(*num_nd)++];
}

int main(int argc, char *argv[]) {
	unsigned int A, B, n, k, b, num_nd, x, max;
	struct nd t[MAX_N << 5], *ptr;
	scanf("%u%u", &A, &B);
	t[0].c[0] = NULL, t[0].c[1] = NULL;
	for (num_nd = 1, n = A; n <= B; ++n) {
		for (ptr = &t[0], k = 32; k; --k) {
			if (b = ((n >> (k - 1)) & 1), !ptr -> c[b]) ptr -> c[b] = init(&num_nd, t);
			ptr = ptr -> c[b];
		}
	}
	for (max = 0, n = A; n <= B; ++n) {
		for (x = 0, ptr = &t[0], k = 32; k; --k) if (ptr -> c[!(b = (n >> (k - 1)) & 1)]) x |= 1 << (k - 1), ptr = ptr -> c[!b]; else ptr = ptr -> c[b]; 
		if (x > max) max = x;
	}
	printf("%u\n", max);
	return 0;
}
