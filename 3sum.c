#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int comp(const void *a, const void *b) {
	return *(const int *)a < *(const int *)b ? -1 : *(const int *)a == *(const int *)b ? 0 : 1;
}

int main(int argc, char *argv[]) {
	unsigned int n = 0, num_distinct, found, idx, idx3, idx2, idx1, idx0; 
	int d, diff, sum, array[MAX_N], array_distinct[MAX_N];
	while (1) {
		scanf("%u", &n);
		if (!n) {
			break;
		}
		for (idx = 0; idx < n; ++idx) {
			scanf("%d", &array[idx]); 
		}
		qsort(array, n, sizeof(int), comp);    
		/*
		for (idx = 0; idx < n; ++idx) {
			printf("%d ", array[idx]); 
		}
		*/
		for (idx = 0, idx1 = 0; idx < n; ++idx1) {
			d = array_distinct[idx1] = array[idx++];
			while (idx < n && array[idx] == d) {
				++idx;
			}
		}
		num_distinct = idx1;
		/*
		for (idx = 0; idx < num_distinct; ++idx) {
			printf("%d ", array_distinct[idx]); 
		}
		printf("\n");
		*/
		found = 0;
		for (idx3 = num_distinct; idx3 > 0; --idx3) {   /* rhs */
			d = array_distinct[idx3 - 1];
			for (idx2 = num_distinct - 1; idx2 > 1; --idx2) {   /* largest elem of lhs */
				if (idx2 == idx3 - 1) {
					continue;
				}
				diff = d - array_distinct[idx2]; 
				for (idx0 = 0, idx1 = idx2 - 1; idx0 < idx1;) {  /* 2 smaller elems of lhs */
					if ((sum = array_distinct[idx0] + array_distinct[idx1]) < diff) {
						++idx0;
					}else if (sum > diff) {
						--idx1;
					}else if (idx0 != idx3 - 1 && idx1 != idx3 - 1) {
						found = 1;
						break;
					}
				}
				if (found) {
					break;
				}
			}
			if (found) {
				break;
			}
		}
		if (found) {
			printf("%d\n", d);
		}else {
			printf("no solution\n");
		}
	}
	return 0;
}
