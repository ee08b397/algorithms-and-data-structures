/* http://m.hackerrank.com/contests/w7/challenges/helix */

#include <stdio.h>

#define MAX_N 100000
#define KEY_T int

static unsigned int num_elem;

static struct elem {
	unsigned int size, rev;
	KEY_T key;
	struct elem *left, *right, *parent;
} E[MAX_N + 2], *root, *M[MAX_N + 2];

unsigned int size(const struct elem *const e) {
	return e ? e->size : 0;
}

unsigned int update(struct elem *const e) {
	return e ? (e->size = size(e->left) + size(e->right) + 1) : 0;
}

struct elem * new_elem(const KEY_T key, struct elem *const left, struct elem *const right) {
	if (left) left->parent = &E[num_elem];
	if (right) right->parent = &E[num_elem];
	E[num_elem].key = key, E[num_elem].left = left, E[num_elem].right = right, E[num_elem].rev = 0, E[num_elem].parent = NULL, update(&E[num_elem]);
	return M[key] = &E[num_elem++];
}

struct elem * init(const KEY_T min, const KEY_T max) {
	KEY_T mid;
	return min > max ? NULL : min < max ? (mid = min + ((max - min) >> 1), new_elem(mid, init(min, mid - 1), init(mid + 1, max))) : new_elem(min, NULL, NULL);
}

void push_down(struct elem *const e) {
	struct elem *tmp;
	if (!e || !e->rev) return;
	if (e->left) e->left->rev ^= 1;
	if (e->right) e->right->rev ^= 1;
	tmp = e->left, e->left = e->right, e->right = tmp, e->rev = 0;
}

struct elem * zig(struct elem *const e) {
	struct elem *l, *lr;
	/* push_down(e); // this is done by the caller already */
	push_down(e->left), lr = (l = e->left)->right, l->right = e, l->parent = e->parent, e->parent = l, e->left = lr;
	if (lr) lr->parent = e;
	update(e), update(l);
	return l;
}

struct elem * zag(struct elem *const e) {
	struct elem *r, *rl;
	/* push_down(e); // this is done by the caller already */
	push_down(e->right), rl = (r = e->right)->left, r->left = e, r->parent = e->parent, e->parent = r, e->right = rl;
	if (rl) rl->parent = e;
	update(e), update(r);
	return r;
}

struct elem * splay(struct elem *const p, struct elem *const e) {
	struct elem *z, **c;
	if (p == e->parent) return e;
	if (e->parent->parent) push_down(e->parent->parent), c = (e->parent == e->parent->parent->left ? &(e->parent->parent->left) : &(e->parent->parent->right)); else c = NULL;
	push_down(e->parent), z = (e == e->parent->left ? zig(e->parent) : zag(e->parent));
	if (c) *c = z;
	return splay(p, z);
}

struct elem * kth(struct elem *const e, const unsigned int k) {
	unsigned int ls;
	push_down(e), ls = size(e->left);
	return k < ls ? kth(e->left, k) : k == ls ? e : kth(e->right, k - ls - 1);
}

unsigned int idx(struct elem *const e) {
	unsigned int c, top;
	struct elem *ptr;
	static struct elem *stack[MAX_N + 2];
	for (top = 0, ptr = e; ptr; ptr = ptr->parent) stack[top++] = ptr;
	while (top--) push_down(stack[top]);
	for (c = size(e->left), ptr = e; ptr->parent; ptr = ptr->parent) if (ptr == ptr->parent->right) c += size(ptr->parent->left) + 1;
	return c;
}

void rev(const KEY_T a, const KEY_T b) {
	struct elem *prev, *next, *rl;
	prev = kth(root, a - 1), next = kth(root, b + 1), root = splay(NULL, prev), root->right = splay(root, next), push_down(rl = root->right->left), rl->rev = 1;
}

int main(int argc, char *argv[]) {
	unsigned int N, Q, q, k;
	KEY_T a, b;
	scanf("%u%u", &N, &Q), num_elem = 0, root = init(0, N + 1);
	while (Q--) {
		scanf("%u", &q);
		if (1 == q) scanf("%d%d", &a, &b), rev(a, b); else if (2 == q) scanf("%d", &a), printf("element %d is at position %u\n", a, idx(M[a])); else if (3 == q) scanf("%u", &k), printf("element at position %u is %d\n", k, kth(root, k)->key);
	}
	return 0;
}
