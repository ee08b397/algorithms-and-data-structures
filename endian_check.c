#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	long x = 0x34333231;
	char *y = (char *) &x;
	if(strncmp(y,"1234", 4))
		printf("Big Endian\n");
	else
		printf("little Endian\n");
	return 0;
}
