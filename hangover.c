#include <stdio.h>  

#define MAX_N 301
  
int main(int argc, char *argv[]) {  
	unsigned int s, min, max, mid;
	double l, length[MAX_N];
	length[0] = 0.0;
	for (s = 1; s < MAX_N; ++s) {
		length[s] = length[s - 1] + 1.0 / (s + 1.0);
	}
	while (1) {  
		scanf("%lf", &l);
		if (!l) return 0;
		min = 0;
		max = MAX_N - 1;
		while (max > min) {
			mid = (min + max) >> 1;
			if (length[mid] < l) {
				min = mid + 1;
			}else {
				max = mid;
			}
		}
		printf("%u card(s)\n", min);
	}
	return 0;  
}  
