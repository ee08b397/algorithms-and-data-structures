#include <stdio.h>
#include <math.h>

#define EPS 1e-9

int main(int argc, char *argv[]) {
	double X, Y, C, a, b, sq, min, max, mid; 
	while (scanf("%lf %lf %lf", &X, &Y, &C) != EOF) {
		min = 0;
		max = X < Y ? X : Y;
		while (max - min > EPS) {
			mid = (max + min) / 2; 
			sq = mid * mid;
			a = sqrt(X * X - sq);
			b = sqrt(Y * Y - sq) ;
			if (a * b < C * (a + b)) max = mid; else min = mid;
		}
		printf( "%.3f\n", min) ;
	}
	return 0 ;
}
