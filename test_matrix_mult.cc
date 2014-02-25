#include <iostream>
#include <cstdio>
#include <ctime>

#define N 400
#define LATTICE_SIZE 1000000 

/* g++ -Wall -O3 -lrt test_matrix_mult.cc */

/*./a.out 2>/dev/null */

double rrand(void) {
	int val;
	FILE *rnd = fopen("/dev/urandom", "rb");
	fread(&val, sizeof(int), 1, rnd);
	fclose(rnd);
	if (val < 0) {
		val *= -1;
	}
	return 1.0 * (val % (2 * LATTICE_SIZE) - LATTICE_SIZE) / LATTICE_SIZE;  
}

int main(int argc, char *argv[]) {
	size_t i, j, k;
	struct timespec start, end;
	double cpu_t;
	double A[N][N], B[N][N], C[N][N]; 
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			A[i][j] = rrand();
			B[i][j] = rrand();
			C[i][j] = 0.0;
		}
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	for (j = 0; j < N; ++j) {
		for (k = 0; k < N; ++k) {
			for (i = 0; i < N; ++i) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	cpu_t = 1.0 * (end.tv_sec - start.tv_sec) + 1.0 * (end.tv_nsec - start.tv_nsec) / 1000000000;
	std::cout << "jki-order CPU time: " << cpu_t << "\n";
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			std::cerr << C[i][j] << ",";
			C[i][j] = 0.0;
		}
		std::cerr << "\n";
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	for (i = 0; i < N; ++i) {
		for (k = 0; k < N; ++k) {
			for (j = 0; j < N; ++j) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			std::cerr << C[i][j] << ",";
		}
		std::cerr << "\n";
	}
	cpu_t = 1.0 * (end.tv_sec - start.tv_sec) + 1.0 * (end.tv_nsec - start.tv_nsec) / 1000000000;
	std::cout << "jki-order CPU time: " << cpu_t << "\n";
	return 0;
}
