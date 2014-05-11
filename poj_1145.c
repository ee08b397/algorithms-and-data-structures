#include <stdio.h>

int parse_whitespace(char *const next_char) {
	char c;
	int num = 0;
	for (c = *next_char ? *next_char : getc(stdin), *next_char = '\0'; ' ' == c || '\r' == c || '\n' == c || '\t' == c; ++num, c = getc(stdin));
	*next_char = c;
	return num;
}

int parse_num(char *const next_char, int *const is_empty) {
	char c;
	int num = 0, sgn = 1;
	for (*is_empty = 1, c = *next_char ? *next_char : getc(stdin), *next_char = '\0'; ('0' <= c && '9' >= c) || '-' == c || '+' == c; c = getc(stdin)) if ('-' == c) sgn = -1; else num = num * 10 + (c - '0'), *is_empty = 0;
	*next_char = c;
	return sgn * num;
}

int parse_s_expr(char *const next_char, const int sum, int *const is_empty) {
	char c;
	int num, empty_left_chld, empty_right_chld, ret = 0;
	parse_whitespace(next_char);
	for (c = *next_char ? *next_char : getc(stdin), *next_char = '\0'; '(' != c; c = getc(stdin)); /* parse '(' */
	num = parse_num(next_char, is_empty);
	if (!*is_empty) {
		ret |= parse_s_expr(next_char, sum - num, &empty_left_chld);
		ret |= parse_s_expr(next_char, sum - num, &empty_right_chld);
		if (empty_left_chld && empty_right_chld && num == sum) ret = 1;
	}
	for (c = *next_char ? *next_char : getc(stdin), *next_char = '\0'; ')' != c; c = getc(stdin)); /* parse ')' */
	*next_char = '\0';
	return ret;
}

int main(int argc, char *argv[]) {
	char next_char = '\0';
	int sum, is_empty = 0;
	while (EOF != next_char) {
		sum = parse_num(&next_char, &is_empty);
		printf(parse_s_expr(&next_char, sum, &is_empty) ? "yes\n" : "no\n");
		parse_whitespace(&next_char);
	}
	return 0;
}
