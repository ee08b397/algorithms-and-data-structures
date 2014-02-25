#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
	printf("%d\n", pow(2.0, 51) == pow(2.0, 51) + 1);
	printf("%d\n", pow(2.0, 52) == pow(2.0, 52) + 1);
	printf("%d\n", 1.99 * pow(2.0, 52) == 1.99 * pow(2.0, 52) + 1);
	printf("%d\n", pow(2.0, 53) == pow(2.0, 53) + 1);
	printf("%d\n", 3.0 * pow(2.0, 53) == 3.0 * pow(2.0, 53) + 1);
	return 0;
}
