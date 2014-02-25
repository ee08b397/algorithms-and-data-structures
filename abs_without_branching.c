#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[]) {
	int v;
	int mask;
	scanf("%d", &v);
	mask = v >> (CHAR_BIT * sizeof(int) - 1);
	printf("%d\n", (v + mask) ^ mask); 
	return 0;
}
