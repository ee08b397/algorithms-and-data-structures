#include <stdio.h>

#define MAX_LEN 250
#define ADD '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'
#define LPAREN '('
#define RPAREN ')'

struct node {
	char operator, operand;
	unsigned int num_lparen, num_rparen;
	struct node *l_operand, *r_operand;
};

struct node *parse_expr(char *const, size_t *const, struct node *const);

struct node* parse_operator(char *const next_char, size_t *const n_idx, struct node *const mem) {
	struct node *result = &mem[(*n_idx)++];
	result -> operator = *next_char;
	*next_char = getchar();
	result -> num_lparen = 0;
	result -> num_rparen = 0;
	return result;
}

struct node *parse_factor(char *const next_char, size_t *const n_idx, struct node *const mem) {
	struct node *result;
	if (*next_char == LPAREN) {
		*next_char = getchar();
		result = parse_expr(next_char, n_idx, mem);
		*next_char = getchar();   /* skip matching ')' */  
		return result;
	}
	result = &mem[(*n_idx)++];
	result -> operator = '\0';
	result -> operand = *next_char;
	*next_char = getchar();
	result -> l_operand = NULL;
	result -> r_operand = NULL;
	result -> num_lparen = 0;
	result -> num_rparen = 0;
	return result;
}

struct node *parse_term(char *const next_char, size_t *const n_idx, struct node *const mem) {
	struct node *t = parse_factor(next_char, n_idx, mem), *op;
	while (*next_char != '\n' && *next_char != RPAREN && *next_char != ADD && *next_char != SUB) {
		op = parse_operator(next_char, n_idx, mem);
		op -> l_operand = t;
		op -> r_operand = parse_factor(next_char, n_idx, mem);
		t = op;
	}
	return t;
}

struct node *parse_expr(char *const next_char, size_t *const n_idx, struct node *const mem) {
	struct node *t = parse_term(next_char, n_idx, mem), *op;
	while (*next_char != '\n' && *next_char != RPAREN) {
		op = parse_operator(next_char, n_idx, mem);
		op -> l_operand = t;
		op -> r_operand = parse_term(next_char, n_idx, mem);
		t = op;
	}
	return t;
}

void print_expr(struct node *result) {
	unsigned int p;
	size_t s_size = 1;
	struct node *s[MAX_LEN] = {result}, *ptr; 
	while (s_size) {
		ptr = s[--s_size];
		if (ptr -> l_operand) {
			ptr -> l_operand -> num_lparen = ptr -> num_lparen;
			ptr -> r_operand -> num_rparen = ptr -> num_rparen;
			s[s_size++] = ptr -> r_operand;
			if (ptr -> operator == SUB) {
				if (ptr -> r_operand -> operator == ADD || ptr -> r_operand -> operator == SUB) {
					++(ptr -> r_operand -> num_lparen);
					++(ptr -> r_operand -> num_rparen);
				}
			}else if (ptr -> operator == DIV) {
				if (ptr -> r_operand -> operator) {
					++(ptr -> r_operand -> num_lparen); 
					++(ptr -> r_operand -> num_rparen); 
				}
			}else if (ptr -> operator == MUL) {
				if (ptr -> r_operand -> operator == ADD || ptr -> r_operand -> operator == SUB) {
					++(ptr -> r_operand -> num_lparen); 
					++(ptr -> r_operand -> num_rparen); 
				}
			}
			ptr -> r_operand = NULL;
			s[s_size++] = ptr;
			s[s_size++] = ptr -> l_operand;
			if (ptr -> operator == MUL || ptr -> operator == DIV) {
				if (ptr -> l_operand -> operator == ADD || ptr -> l_operand -> operator == SUB) {
					++(ptr -> l_operand -> num_lparen); 
					++(ptr -> l_operand -> num_rparen);
				}
			}
			ptr -> l_operand = NULL;
		}else if (ptr -> operator) {
			putchar(ptr -> operator);
		}else {
			for (p = 0; p < ptr -> num_lparen; ++p) {
				putchar('(');
			}
			putchar(ptr -> operand);
			for (p = 0; p < ptr -> num_rparen; ++p) {
				putchar(')');
			}
		}
	}
	putchar('\n');
}

int main(int argc, char *argv[]) {
	char next_char;
	unsigned int T;
	size_t n_idx;
	struct node mem[MAX_LEN];
	T = 0;
	while (1) {
		next_char = getchar();
		if (next_char >= '0' && next_char <= '9') {
			T = 10 * T + (next_char - '0');
		}else {
			break;
		}
	}
	while (T--) {
		n_idx = 0;
		next_char = getchar();
		print_expr(parse_expr(&next_char, &n_idx, mem));
	}
	return 0;
}
