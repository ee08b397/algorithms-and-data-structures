__attribute__((optimize("-O2"))) 
int return_zero() {
	long x;
	x = 11;
	x += 12;
	x *= 13;
	x /= 14;
	return 0;
}

__attribute__((optimize("-O2"))) 
int main(int argc, char *argv[]) {
	long x;
	x = 11;
	x += 12;
	x *= 13;
	x /= 14;
	return 0;
}

