#include <stdio.h>
#include <limits.h>
#include <assert.h>

#define MAX_N 1024
#define KEY_T int
#define MIN_KEY INT_MIN
#define MAX_KEY INT_MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

unsigned int num_elem;

struct elem {
	unsigned int size;
	KEY_T key;
	struct elem *left, *right;
} E[MAX_N];

unsigned int size(const struct elem *const e) {
	return e ? e->size : 0;
}

unsigned int update(struct elem *const e) {
	return e ? (e->size = size(e->left) + size(e->right) + 1) : 0;
}

struct elem * new_elem(const KEY_T key) {
	E[num_elem].key = key, E[num_elem].left = NULL, E[num_elem].right = NULL, E[num_elem].size = 1;
	return &E[num_elem++];
}

struct elem * zig(struct elem *const e) {
	struct elem *l, *lr;
	lr = (l = e->left)->right, l->right = e, e->left = lr, update(e), update(l);
	return l;
}

struct elem * zag(struct elem *const e) {
	struct elem *r, *rl;
	rl = (r = e->right)->left, r->left = e, e->right = rl, update(e), update(r);
	return r;
}

struct elem * splay(struct elem *const e, const KEY_T key) {
	struct elem *_e;
	if (!e || key == e->key) return e;
	_e = e;
	if (key < e->key) {
		if (!e->left) return e;
		if (key < e->left->key) e->left->left = splay(e->left->left, key), _e = zig(e); else if (key > e->left->key && (e->left->right = splay(e->left->right, key))) e->left = zag(e->left);
		return _e->left ? zig(_e) : _e;
	}
	if (!e->right) return e;
	if (key > e->right->key) e->right->right = splay(e->right->right, key), _e = zag(e); else if (key < e->right->key && (e->right->left = splay(e->right->left, key))) e->right = zig(e->right);
	return _e->right ? zag(_e) : _e;
}

struct elem *find_min(struct elem *const e) {
	return splay(e, MIN_KEY);
}

struct elem *find_max(struct elem *const e) {
	return splay(e, MAX_KEY);
}

struct elem *del_min(struct elem *const e) {
	struct elem *m, *r;
	if (!(m = find_min(e))) return NULL;
	#ifdef DEBUG
	printf("del_min: min == %d\n", m->key);
	#endif
	r = m->right;
	/* free(m); */
	return r;
}

struct elem *del_max(struct elem *const e) {
	struct elem *m, *r;
	if (!(m = find_max(e))) return NULL;
	#ifdef DEBUG
	printf("del_max: max == %d\n", m->key);
	#endif
	r = m->left;
	/* free(m); */
	return r;
}

struct elem * ins(struct elem *const e, const KEY_T key) {
	struct elem *_e, *n;
	if (!e) return new_elem(key);
	_e = splay(e, key);
	if (key == _e->key) return _e;
	n = new_elem(key);
	if (key < _e->key) n->right = _e, n->left = _e->left, _e->left = NULL; else n->left = _e, n->right = _e->right, _e->right = NULL;
	update(_e), update(n);
	return n;
}

struct elem *del(struct elem *const e, const KEY_T key) {
	struct elem *d, *r;
	if (!(d = splay(e, key)) || key != d->key) return d;
	if (d->left) (r = find_max(d->left))->right = d->right, update(r); else if (d->right) (r = find_min(d->right))->left = d->left, update(r); else r = NULL;
	/* free(d); */
	return r;
}

struct elem * kth(struct elem *const e, const unsigned int k) {
	unsigned int ls;
	return ls = size(e->left), k < ls ? kth(e->left, k) : k == ls ? e : kth(e->right, k - ls - 1);
}

unsigned int count(struct elem *const e, const KEY_T key) {
	return !e ? 0 : e->key < key ? size(e->left) + 1 + count(e->right, key) : count(e->left, key);
}


void preorder(struct elem *const e) {
	if (!e) return;
	printf("%d ", e->key);
	preorder(e->left), preorder(e->right);
}

int main(int argc, char *argv[]) {
	struct elem *e;
	e = new_elem(100), (((e->left = new_elem(50))->left = new_elem(40))->left = new_elem(30))->left = new_elem(20), e->right = new_elem(200), e = ins(e, 25); /* e = splay(e, 20); */
	preorder(e);
	printf("\n");
	find_min(NULL), find_max(NULL);
	printf("min == %d\n", (e = find_min(e))->key);
	assert(20 == e->key);
	printf("max == %d\n", (e = find_max(e))->key);
	assert(200 == e->key);
	printf("min == %d\n", (e = find_min(e))->key);
	assert(20 == e->key);
	printf("max == %d\n", (e = find_max(e))->key);
	assert(200 == e->key);
	printf("min == %d\n", (e = find_min(e))->key);
	assert(20 == e->key);
	preorder(e);
	printf("\n");
	printf("max == %d\n", (e = find_max(e))->key);
	assert(200 == e->key);
	preorder(e);
	printf("\n");
	e = del_min(e);
	e = del_min(e);
	e = del_min(e);
	e = del_min(e);
	e = del_min(e);
	e = del_min(e);
	preorder(e);
	printf("\n");
	e = del_min(e);
	e = ins(e, 25);
	e = ins(e, 50);
	e = ins(e, 40);
	e = ins(e, 20);
	e = ins(e, 100);
	e = ins(e, 200);
	e = ins(e, 30);
	preorder(e);
	printf("\n");
	e = del_max(e);
	e = del_max(e);
	e = del_max(e);
	e = del_max(e);
	e = del_max(e);
	e = del_max(e);
	preorder(e);
	printf("\n");
	e = del_max(e);
	preorder(e);
	printf("\n");
	e = new_elem(100), (((e->left = new_elem(50))->left = new_elem(40))->left = new_elem(30))->left = new_elem(20), e->right = new_elem(200), e = ins(e, 25); /* e = splay(e, 20); */
	preorder(e);
	printf("\n");
	e = del(e, 30);
	preorder(e);
	printf("\n");
	e = del(e, 20);
	preorder(e);
	printf("\n");
	e = del(e, 25);
	preorder(e);
	printf("\n");
	e = del(e, 101);
	preorder(e);
	printf("\n");
	e = del(e, 200);
	preorder(e);
	printf("\n");
	return 0;
}
