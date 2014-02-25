#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000

struct P {
	size_t s, n;
	struct P *left, *right, *parent;
};

struct P *init(const size_t start, const size_t end, size_t *const q_offset, size_t *const idx, struct P *const root, struct P q[]) {
	size_t mid;
	struct P *cq;
	if (start > end) return NULL;   /* range is empty */ 
	cq = &q[(*q_offset)++];		
	cq -> parent = root; 
	if (start == end) {   /* range has only 1 element */
		cq -> right = cq -> left = NULL;
		cq -> s = 1;
		cq -> n = (*idx)++; 
		/* printf("cq -> s == %u\n", cq -> s); */
		return cq;
	}
	mid = (start + end) >> 1;
	cq -> n = MAX_N;
	cq -> left = init(start, mid, q_offset, idx, cq, q);
	cq -> right = init(mid + 1, end, q_offset, idx, cq, q);
	cq -> s = (cq -> left ? cq -> left -> s : 0) + (cq -> right ? cq -> right -> s : 0);
	/* printf("cq -> s == %u\n", cq -> s); */
	return cq;
}

void insert(const size_t p, const size_t v, struct P *const root, size_t result[]) {
	struct P *ptr = root;
	if (ptr -> n != MAX_N) {
		result[ptr -> n] = v; 
		while (ptr) {
			--(ptr -> s);
			ptr = ptr -> parent;
		}
	}else {
		if (ptr -> left) {
			if (p < ptr -> left -> s) insert(p, v, ptr -> left, result); else insert(p - ptr -> left -> s, v, ptr -> right, result);
		}else {
			insert(p, v, ptr -> right, result);
		}
	}
}

int main(int argc, char *argv[]) {
	size_t N, n, q_offset, idx, p[MAX_N], v[MAX_N], result[MAX_N];
	struct P *q = (struct P *)malloc(sizeof(struct P) * (MAX_N << 1)), *root;
	while (scanf("%lu", &N) != EOF) {
		if (!N) return 0;
		q_offset = 0;
		idx = 0;
		root = init(0, N - 1, &q_offset, &idx, NULL, q);
		for (n = 0; n < N; ++n) {
			scanf("%lu%lu", &p[n], &v[n]); 
		}
		for (n = N; n; --n) {
			insert(p[n - 1], v[n - 1], root, result);
		}
		for (n = 0; n + 1 < N; ++n) {
			printf("%lu ", result[n]);
		}
		printf("%lu\n", result[n]);
	}
	free(q);
	return 0;
}
