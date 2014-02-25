#include <stdio.h>

int __josephus(const int n, const int k, const int sp) {
	int new_sp, survivor;
	if(n == 1) return 1;
	new_sp = (sp + k - 2) % n + 1;   /* compute new starting point from previous starting point */
	return (survivor = __josephus(n - 1, k, new_sp)) < new_sp ? survivor : survivor + 1;
}

int josephus(const int n, const int k) {
	return __josephus(n, k, 1);
}

int main(int argc, char *argv[]) {    /* assume inital numberings are 1, .., n */
	int n;
	for (n = 1; n <= 16; ++n) { 
		printf("%d ", josephus(n, 2));
	}
	printf("\n");
	return 0;
}
