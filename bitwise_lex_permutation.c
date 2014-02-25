#include <stdio.h>

int main(int argc, char *argv[]) {
	unsigned int a, c, r;
	while (1) {
		scanf("%u", &a);
		if (!a) {
			return 0;
		}
		c = (a & -a);
		r = a + c;
		printf("%u\n", ((((r ^ a) >> 2) / c) | r));
	}
	return 0;
}


