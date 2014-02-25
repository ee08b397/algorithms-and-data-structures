#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_RULE 26
#define MAX_NUM_TERM 26
#define START_SYMBOL 'S'

struct list_node {
	char r[2]; 
	struct list_node *next;
};

void delete_list(struct list_node * const hdr) {
	struct list_node *ptr = hdr, *next;
	while (ptr) {
		next = ptr -> next;
		free(ptr);
		ptr = next;
	}
}

int main(int argc, char *argv[]) {
	char c, lhs, ***P;
	size_t n, i, j, k, g, length = 0;
	struct list_node * nt_rules[MAX_NUM_RULE], * unit_rules[MAX_NUM_TERM], *ln_ptr = NULL, *ptr = NULL, *u_ptr = NULL, *ln = NULL, *g_ptr = NULL;
	for (n = 0; n < MAX_NUM_RULE; ++n) {
		nt_rules[n] = NULL;
	}
	for (n = 0; n < MAX_NUM_TERM; ++n) {
		unit_rules[n] = NULL;
	}
	while (scanf("%c", &c) != EOF) {
		if (c == '#') {
			break;
		}else {
			lhs = c;
			/* printf("%c->", lhs); */ 
			scanf("%c%c", &c, &c);    /* skip "->" */
			while (c != '\n') {
				scanf("%c", &c);    /* skip "->" */
				if (c >= 'a' && c <= 'z') {
					ptr = (struct list_node *)malloc(sizeof(struct list_node));
					ptr -> r[0] = lhs;
					ptr -> next = unit_rules[c - 'a'];
					/* if (unit_rules[c - 'a'] */
					unit_rules[c - 'a'] = ptr;
					/* printf("%c|", c); */
				}else if (c >= 'A' && c <= 'Z') {
					ptr = (struct list_node *)malloc(sizeof(struct list_node));
					ptr -> r[0] = c;
					scanf("%c", &(ptr -> r[1]));
					ptr -> next = nt_rules[lhs - 'A'];
					nt_rules[lhs - 'A'] = ptr;
					/* printf("%c%c|", ptr -> r[0], ptr -> r[1]); */
				}
			}
			/*printf("\n"); */
		}
	}
	while (scanf("%c", &c) != EOF) {
		if (c == '\n') {
			if (ln) { 
				ptr -> r[0] = '\0';
				ptr -> next = NULL;
				/*printf("\n%lu\n", length);*/
				P = (char ***)malloc(length * sizeof(char **)); 	
				for (i = 0; i < length; ++i) {
					P[i] = (char **)malloc(length * sizeof(char *)); 
					for (j = 0; j < length; ++j) {
						P[i][j] = (char *)malloc(MAX_NUM_TERM * sizeof(char));
						for (k = 0; k < MAX_NUM_TERM; ++k) {
							P[i][j][k] = 0;
						}
					}
				}
				i = 0;
				ln_ptr = ln;
				while (ln_ptr -> r[0]) {
					u_ptr = unit_rules[ln_ptr -> r[0] - 'a'];
					while (u_ptr) {
						P[i][0][u_ptr -> r[0] - 'A'] = 1; 
						u_ptr = u_ptr -> next;
					}
					++i;
					ln_ptr = ln_ptr -> next;
				}
				for (i = 2; i <= length; ++i) {
					for (j = 1; j + i <= length + 1; ++j) {
						for (k = 1; k + 1 <= i; ++k) {
							for (g = 0; g < MAX_NUM_RULE; ++g) {
								g_ptr = nt_rules[g]; 
								while (g_ptr) {
									if (P[j - 1][k - 1][g_ptr -> r[0] - 'A'] && P[j + k - 1][i - k - 1][g_ptr -> r[1] - 'A']) {
										P[j - 1][i - 1][g] = 1;
									}
									g_ptr = g_ptr -> next;
								}
							}
						}
					}
				}
				printf(P[0][length - 1][START_SYMBOL - 'A'] ? "YES\n" : "NO\n"); 
				delete_list(ln); 
				for (i = 0; i < length; ++i) {
					for (j = 0; j < length; ++j) {
						free(P[i][j]);
					}
					free(P[i]);
				}
				free(P);
			}
			length = 0;
			ln = (struct list_node *)malloc(sizeof(struct list_node));
			ptr = ln;
		}else {
			ptr -> r[0] = c; 
			ptr -> next = (struct list_node *)malloc(sizeof(struct list_node));
			ptr = ptr -> next; 
			++length;
		}
	}
	/*
	free(ln);
	for (n = 0; n < MAX_NUM_RULE; ++n) {
		delete_list(nt_rules[n]);
	}
	for (n = 0; n < MAX_NUM_TERM; ++n) {
		delete_list(unit_rules[n]);
	}
	*/
	return 0;
}
