#include <stdio.h>

int main(int argc, char *argv[]) {
	int a, b;
	printf("Enter value for a:\n"); scanf("%d", &a);
	printf("Enter value for b:\n"); scanf("%d", &b);
	printf("xchg\n");
	asm volatile("xchg %0, %1" : "=r" (a), "=r" (b) : "0" (a), "1" (b));
	printf("The value of a is %d\n", a);
	printf("The value of b is %d\n", b);
	printf("%d %d\n", a, b);
	return 0;
}
