#include <stdio.h>
#include <stdlib.h>

#define N_CHAR 28
#define ANY_CHAR '?'
#define KLEENE_STAR '*'
#define ANY_CHAR_OFFSET 2
#define KLEENE_STAR_OFFSET 1
#define MAX_N 100010
#define MAX_PATTERN_LEN 6
#define MAX_WORD_LEN 20

struct node {
	struct node *next[N_CHAR];
	struct match *matches, *last_match;
};

struct match {
	unsigned int n; 
	struct match *next;
};

int comp_matches(const void *const a, const void *const b) {
	return *((const unsigned int *const)a) < *((const unsigned int *const)b) ? -1 : 1; 
}

unsigned int get_next_idx(const char c) {
	return c >= 'a' && c <= 'z' ? c - 'a' : c == ANY_CHAR ? N_CHAR - ANY_CHAR_OFFSET : N_CHAR - KLEENE_STAR_OFFSET;
}

void init_node(struct node *const root) {
	unsigned int n;
	root -> matches = NULL;
	root -> last_match = NULL;
	for (n = 0; n < N_CHAR; ++n) root -> next[n] = NULL;
}

void insert(const char *const p, unsigned int *const t_idx, struct node *const t, struct node *const root, struct match *const m) {
	unsigned int p_idx, offset = 0;
	if (!*p) {
		if (root -> last_match) root -> last_match -> next = m; else root -> matches = m;
		root -> last_match = m;
		m -> next = NULL;
		return;
	}
	if (*p == KLEENE_STAR) while (*(p + offset + 1) == KLEENE_STAR) ++offset;
	p_idx = get_next_idx(*(p + offset));
	if (!root -> next[p_idx]) init_node(root -> next[p_idx] = t + (*t_idx)++);
	insert(p + offset + 1, t_idx, t, root -> next[p_idx], m);
}

void dfs(const char *const w, unsigned int *const m_idx, unsigned int matches[], const struct node *const root) {
	unsigned int i; 
	const struct match *ptr; 
	if (!root) return; 
	if (!*w) {
		ptr = root -> matches;
		while (ptr) {
			matches[(*m_idx)++] = ptr -> n;
			ptr = ptr -> next;
		}
		if (root -> next[N_CHAR - KLEENE_STAR_OFFSET]) {
			ptr = root -> next[N_CHAR - KLEENE_STAR_OFFSET] -> matches;
			while (ptr) {
				matches[(*m_idx)++] = ptr -> n;
				ptr = ptr -> next;
			}
		}
		return;
	}
	dfs(w + 1, m_idx, matches, root -> next[get_next_idx(*w)]);
	if (root -> next[N_CHAR - ANY_CHAR_OFFSET]) dfs(w + 1, m_idx, matches, root -> next[N_CHAR - ANY_CHAR_OFFSET]);
	if (root -> next[N_CHAR - KLEENE_STAR_OFFSET]) {
		for (i = 0; w[i]; ++i) dfs(w + i, m_idx, matches, root -> next[N_CHAR - KLEENE_STAR_OFFSET]);
		dfs(w + i, m_idx, matches, root -> next[N_CHAR - KLEENE_STAR_OFFSET]);
	}
}

void print_matches(const char *const w, const struct node *const root, unsigned int *const matches) {
	unsigned int m_idx = 0, i;
	dfs(w, &m_idx, matches, root);
	qsort(matches, m_idx, sizeof(unsigned int), comp_matches);
	if (m_idx) {
		printf("%u", matches[0]);
		for (i = 1; i < m_idx; ++i) if (matches[i] != matches[i - 1]) printf(" %u", matches[i]);
		printf("\n");
	}else printf("Not match\n");
}

int main(int argc, char *argv[]) {
	unsigned int N, M, n, t_idx, *matches = (unsigned int *)malloc(MAX_N * sizeof(unsigned int));
	char p[MAX_PATTERN_LEN + 1], w[MAX_WORD_LEN + 1]; 
	struct node *t = (struct node *)malloc((MAX_PATTERN_LEN + 1) * MAX_N * sizeof(struct node)), *root;
	struct match *m = (struct match *)malloc(MAX_N * sizeof(struct match));
	init_node(root = &t[0]);
	t_idx = 1;
	scanf("%u%u", &N, &M);
	for (n = 0; n < N; ++n) {
		scanf("%s", p);
		m[n].n = n;
		/* m[n].next = NULL; */
		insert(p, &t_idx, t, root, &m[n]); 
	}
	while (M--) {
		scanf("%s", w);
		print_matches(w, root, matches);
	}
	free(matches);
	free(t);
	free(m);
	return 0;
}
