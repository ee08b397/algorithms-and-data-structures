#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE 10
#define MAX_LEN 10000

char *mult (const char *A, const char *B, char *const result) {
	unsigned int carry, dsum;
	const size_t len_A = strnlen(A, MAX_LEN), len_B = strnlen(B, MAX_LEN);
	size_t idx_result, len_result, offset_A, offset_B;
	if (len_A == 0 || len_B == 0) {
		return NULL;
	}
	len_result = len_A + len_B;
	result[len_result] = '\0';
	for (idx_result = 0; idx_result < len_A + len_B; ++idx_result) {
		result[idx_result] = '0';
	}
	offset_B = len_B;
	while (offset_B) {
		carry = 0;
		offset_A = len_A;
		idx_result = len_result - 1 - len_B + offset_B;
		while (offset_A) {
			dsum = (A[offset_A - 1] - '0') * (B[offset_B - 1] - '0') + carry + (result[idx_result] - '0'); 
			carry = dsum / BASE;
			result[idx_result] = dsum % BASE + '0';
			--offset_A;
			--idx_result;
		}
		while (carry) {
			dsum = carry + (result[idx_result] - '0');
			carry = dsum / BASE;
			result[idx_result] = dsum % BASE + '0';
			--idx_result;
		}
		--offset_B;
	}
	return result;
}

int main(int argc, char *argv[]) {
	size_t n, N;
	char ln[MAX_LEN * 2 + 3], result[MAX_LEN * 2 + 3], *A, *B, *ptr;
	size_t len_A, len_B, idx_result = 0;
	scanf("%lu\n", &N);	
	n = 0;
	while (n++ < N) { 
		fgets(ln, MAX_LEN * 2 + 2, stdin);
		ptr = ln;
		while (*ptr != ' ') {
			++ptr;
		}
		*ptr = '\0';
		A = ln;
		B = ptr + 1;
		len_A = strnlen(A, MAX_LEN);
		len_B = strnlen(B, MAX_LEN);
		/*
		if (len_A > 0 && A[len_A - 1] == '\n') {
			A[len_A - 1] = '\0';
		}
		*/
		if (len_B > 0 && B[len_B - 1] == '\n') {
			B[len_B - 1] = '\0';
			--len_B;
		}
		mult(A, B, result); 
		idx_result = 0;
		while (idx_result + 1 < len_A + len_B && result[idx_result] == '0') {
			++idx_result;
		}
		printf("%s\n", result + idx_result);
	}
	return 0;
}
