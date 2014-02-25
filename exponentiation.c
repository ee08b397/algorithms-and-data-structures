#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DECIMAL_POINT '.' 
#define NUM_DIGITS 5
#define BASE 10

struct num {
	char *digits;
	size_t num_digits, decimal_point;
};

char *__mult (size_t len_A, size_t len_B, const char *A, const char *B, char *const result) {
	unsigned int carry, dsum;
	size_t idx_result, len_result, offset_A, offset_B;
	//char *result;
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

struct num *mult (const struct num *a, const struct num *b) {
	struct num *result = (struct num *)malloc(sizeof(struct num));
	result -> digits = (char *)malloc((result -> num_digits = a -> num_digits + b -> num_digits) + 1); 
	result -> decimal_point = a -> decimal_point + b -> decimal_point; 
	__mult(a -> num_digits, b -> num_digits, (const char *)(a -> digits), (const char *)(b -> digits), result -> digits);
	return result;
}

int main(int argc, char *argv[]) {
	unsigned int e;
	size_t idx, decimal_point_offset;
	char input[NUM_DIGITS + 2], digits[NUM_DIGITS + 1];
	char *ptr, *result_str;
	struct num n, *result, *p, *temp;
	while (scanf("%s %u", input, &e) != EOF) {
		idx = 0;
		n.decimal_point = 0;
		n.num_digits = 0;
		while (input[idx] && input[idx] != DECIMAL_POINT) {
			digits[idx] = input[idx];
			++n.num_digits;
			++idx;
		}
		if (input[idx] == DECIMAL_POINT) {
			while (input[idx + 1]) {
				digits[idx] = input[idx + 1];
				++n.num_digits;
				++idx;
				++n.decimal_point;
			}
		}
		digits[idx] = '\0';
		n.digits = digits;
		result = (struct num *)malloc(sizeof(struct num)); 
		result -> num_digits = 1;
		result -> decimal_point = 0;
		result -> digits = (char *)malloc(2);
		result -> digits[0] = '1';
		result -> digits[1] = '\0';
		p = (struct num *)malloc(sizeof(struct num)); 
		p -> num_digits = n.num_digits;
		p -> decimal_point = n.decimal_point;
		p -> digits = (char *)malloc(n.num_digits + 1);
		strcpy(p -> digits, n.digits);
		while (e) {
			if (e & 1) {
				temp = mult(p, result);
				free(result -> digits);
				free(result);
				result = temp;
			}
			temp = mult(p, p);	
			free(p -> digits);
			free(p);
			p = temp;
			e >>= 1;
		}
		result_str = (char *)malloc(result -> num_digits + 2);
		strncpy(result_str, result -> digits, result -> num_digits - result -> decimal_point);
		if (result -> decimal_point) {
			decimal_point_offset = result -> num_digits - result -> decimal_point;
			result_str[decimal_point_offset] = DECIMAL_POINT;
			strncpy(result_str + decimal_point_offset + 1, result -> digits + result -> num_digits - result -> decimal_point, result -> decimal_point);
			idx = result -> num_digits; 
			while (result_str[idx] == '0') {
				--idx;
			}
			if (result_str[idx] == DECIMAL_POINT) {
				result_str[idx] = '\0';
			}else {
				result_str[idx + 1] = '\0';
			}
		}else {
			result_str[result -> num_digits] = '\0';
		}
		ptr = result_str;
		while (*ptr == '0') {
			++ptr;
		}
		printf("%s\n", ptr);
		free(result_str);
		free(result -> digits);
		free(result);
	}
	return 0;
}
