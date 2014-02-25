#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
	const double phi = (sqrt(5) + 1) / 2;
	unsigned long u, v, x, r;
	while (scanf("%lu%lu", &u, &v) != EOF) {
		if (u > v) {
			x = v;
			r = u - v;
		}else {
			x = u;
			r = v - u;
		}
		printf(x + 1 > phi * r && x < phi * r ? "0\n" : "1\n");
	}
	return 0;
}
