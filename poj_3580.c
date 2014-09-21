/* http://poj.org/problem?id=3580 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define MAX_N 200100
#define KEY_T int
#define KEY_MIN INT_MIN
#define KEY_MAX INT_MAX
#define MAX_OP_LEN 8
#define ADD "ADD"
#define REVERSE "REVERSE"
#define REVOLVE "REVOLVE"
#define INSERT "INSERT"
#define DELETE "DELETE"
#define MIN "MIN"

static unsigned int N, num_elem;

static KEY_T seq[MAX_N];

static struct elem {
	unsigned int size, rev;
	KEY_T key, min, delta;
	struct elem *left, *right, *parent;
} E[MAX_N + 2], *root;

unsigned int size(const struct elem *const e) {
	return e ? e->size : 0;
}

void push_down(struct elem *const e) {
	struct elem *tmp;
	if (!e) return;
	if (e->rev) {
		if (e->left) e->left->rev ^= 1;
		if (e->right) e->right->rev ^= 1;
		tmp = e->left, e->left = e->right, e->right = tmp, e->rev = 0;
	}
	if (e->delta) {
		if (e->left) e->left->delta += e->delta, e->left->key += e->delta, e->left->min += e->delta;
		if (e->right) e->right->delta += e->delta, e->right->key += e->delta, e->right->min += e->delta;
		e->delta = 0;
	}
}

unsigned int push_up(struct elem *const e) {
	KEY_T m;
	e->min = e->key;
	if (e->left && (m = e->left->min) < e->min) e->min = m;
	if (e->right && (m = e->right->min) < e->min) e->min = m;
	return e ? (e->size = size(e->left) + size(e->right) + 1) : 0;
}

struct elem * new_elem(const unsigned int idx, struct elem *const left, struct elem *const right) { /* idx values are 1-based in this function */
	KEY_T key;
	if (left) left->parent = &E[num_elem];
	if (right) right->parent = &E[num_elem];
	key = (1 == idx || N + 2 == idx ? KEY_MAX : seq[idx - 2]);
	E[num_elem].key = key, E[num_elem].delta = 0, E[num_elem].left = left, E[num_elem].right = right, E[num_elem].rev = 0, E[num_elem].parent = NULL, push_up(&E[num_elem]);
	return &E[num_elem++];
}

struct elem * init(const unsigned int min_idx, const unsigned int max_idx) { /* idx values are 1-based in this function */
	unsigned int mid_idx;
	return min_idx > max_idx ? NULL : min_idx < max_idx ? (mid_idx = min_idx + ((max_idx - min_idx) >> 1), new_elem(mid_idx, init(min_idx, mid_idx - 1), init(mid_idx + 1, max_idx))) : new_elem(min_idx, NULL, NULL);
}

struct elem * zig(struct elem *const e) {
	struct elem *l, *lr;
	/* push_down(e); // this is done by the caller already */
	push_down(e->left), lr = (l = e->left)->right, l->right = e, l->parent = e->parent, e->parent = l, e->left = lr;
	if (lr) lr->parent = e;
	push_up(e), push_up(l);
	return l;
}

struct elem * zag(struct elem *const e) {
	struct elem *r, *rl;
	/* push_down(e); // this is done by the caller already */
	push_down(e->right), rl = (r = e->right)->left, r->left = e, r->parent = e->parent, e->parent = r, e->right = rl;
	if (rl) rl->parent = e;
	push_up(e), push_up(r);
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

struct elem * splay_interval(const unsigned int a, const unsigned int b) {
	struct elem *prev, *next;
	prev = kth(root, a - 1), next = kth(root, b + 1), root = splay(NULL, prev), root->right = splay(root, next);
	return root->right->left;
}

void add(const unsigned int a, const unsigned b, const KEY_T delta) {
	struct elem *interval;
	push_down(interval = splay_interval(a, b)), interval->delta = delta, interval->key += delta, interval->min += delta;
}

void reverse(const unsigned int a, const unsigned int b) {
	struct elem *interval;
	push_down(interval = splay_interval(a, b)), interval->rev = 1;
}

void revolve(const unsigned int a, const unsigned int b, const unsigned int t) {
	unsigned int s;
	if (!t || !(s = t % (b - a + 1))) return;
	reverse(a, b - s), reverse(b - s + 1, b), reverse(a, b);
}

void insert(const unsigned int k, const KEY_T key) {
	struct elem *p, *q;
	p = kth(root, k), q = kth(root, k + 1), root = splay(NULL, p), root->right = splay(root, q),
assert(!root->right->left),
	E[num_elem].key = key, E[num_elem].min = key, E[num_elem].delta = 0, E[num_elem].left = NULL, E[num_elem].right = NULL, E[num_elem].size = 1, E[num_elem].rev = 0, E[num_elem].parent = root->right, root->right->left = &E[num_elem++], push_up(root->right), push_up(root);
}

void delete(const unsigned int k) {
	splay_interval(k, k), root->right->left = NULL, push_up(root->right), push_up(root); 
}

KEY_T query_min(const unsigned int a, const unsigned int b) {
	struct elem *interval;
	push_down(interval = splay_interval(a, b));
	return interval->min;
}

int main(int argc, char *argv[]) {
	unsigned int M, n, a, b, t;
	KEY_T d;
	char op[MAX_OP_LEN + 1];
	scanf("%u", &N);
	for (n = 0; n < N; ++n) scanf("%d", &seq[n]);
	root = init(1, N + 2);
	scanf("%u", &M);
	while (M--) {
		scanf("%s", op);
		if (!strcmp(op, ADD)) scanf("%u%u%d", &a, &b, &d), add(a, b, d);
		else if (!strcmp(op, REVERSE)) scanf("%u%u", &a, &b), reverse(a, b);
		else if (!strcmp(op, MIN)) scanf("%u%u", &a, &b), printf("%d\n", query_min(a, b));
		else if (!strcmp(op, REVOLVE)) scanf("%u%u%u", &a, &b, &t), revolve(a, b, t);
		else if (!strcmp(op, INSERT)) scanf("%u%d", &a, &d), insert(a, d);
		else if (!strcmp(op, DELETE)) scanf("%u", &a), delete(a);
	}
	return 0;
}
