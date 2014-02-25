#include <stdio.h> 

int main(int argc, char *argv[]) {
	unsigned int c, q, d, n;
	unsigned long t, T;
	scanf("%lu", &T);
	for (t = 1; t <= T; ++t) { 
		scanf("%u", &c);
		c -= (q = c / 25) * 25;
		c -= (d = c / 10) * 10; 
		c -= (n = c / 5) * 5; 
		printf("%lu %u QUARTER(S), %u DIME(S), %u NICKEL(S), %u PENNY(S)\n", t, q, d, n, c);
	}
	return 0;
}
