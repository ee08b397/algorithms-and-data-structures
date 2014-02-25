#include <stdio.h>
#include <stdlib.h>

void skip(size_t * const offset, const char *expr) {
	while (expr[*offset] && (expr[*offset] < '0' || expr[*offset] > '9') && expr[*offset] != '+' && expr[*offset] != '-' && expr[*offset] != '*' && expr[*offset] != '/') {
		++(*offset);
	}
}

int parse_int(size_t * const offset, const char *expr) {
	int num = 0;
	while (expr[*offset] && expr[*offset] >= '0' && expr[*offset] <= '9') {
		num = num * 10 + (expr[*offset] - '0');
		++(*offset);
	}
	return num;
}

double parse_term(size_t * const offset, const char *expr) {
	double term = 0.0;
	skip(offset, expr);
	term = (double)parse_int(offset, expr);
	while (expr[*offset]) {
		skip(offset, expr);
		if (expr[*offset]) {
			if (expr[*offset] == '*') {
				++(*offset);
				skip(offset, expr);
				term *= (double)parse_int(offset, expr);
			}else if (expr[*offset] == '/') {
				++(*offset);
				skip(offset, expr);
				term /= (double)parse_int(offset, expr);
			}else {
				return term;
			}
		}else {
			return term;
		}
		//++(*offset);
	}
	return term;
}

double eval(const char *expr) {
	size_t offset = 0;
	double sum = 0.0;
	if (expr[0]) {
		skip(&offset, expr);
		sum = (double)parse_term(&offset, expr);
		while (expr[offset]) {
			skip(&offset, expr);
			if (expr[offset] == '+') {
				++offset;
				skip(&offset, expr);
				sum += (double)parse_term(&offset, expr);
			}else if (expr[offset] == '-') {
				++offset;
				skip(&offset, expr);
				sum -= (double)parse_term(&offset, expr);
			}else {
				fprintf(stderr, "invalid arithmetic expression\n");
				exit(-1);
			}
		}
		return sum;
	}
	return 0.0;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <arithmetic expression>\n", argv[0]);
		return -1;
	}
	printf("%f\n", eval((const char *)argv[1]));
	return 0;
}
