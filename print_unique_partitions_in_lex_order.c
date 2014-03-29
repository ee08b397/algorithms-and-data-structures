#include <stdio.h>
#include <stdlib.h>

void print_array(const size_t N, const size_t p[]) {
	size_t n;
	for (n = 0; n < N; ++n) printf("%lu ", p[n]);
	printf("\n");
}
 
void print_unique_partitions(const size_t N) {
	size_t k = 1, rem;   /* k : one plus index of last element in partition */
	size_t *const p = (size_t *)malloc(N * sizeof(size_t));  /* array storing the current partition */
	p[k - 1] = N;  /* initial partition : {N} */
	while (1) {
		print_array(k, p);   /* print the current partition */
		/* find next partition */ 
		for (rem = 0; k && p[k - 1] == 1; rem += p[--k]);  /* right-most non-1 value in current partition */
		if (!k) return; 
		--p[k - 1], ++rem;
		/* preserving sorted order of the results */
		while (rem > p[k - 1]) p[k] = p[k - 1], rem -= p[k - 1], ++k;
		p[k++] = rem;
	}
	free(p);
}
 
int main(int argc, char *argv[]) {
	print_unique_partitions(2);
	print_unique_partitions(3);
	print_unique_partitions(4);
	print_unique_partitions(5);
	print_unique_partitions(6);
	return 0;
}
