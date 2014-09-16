#include <stdio.h>

#define MAX_N 1024
#define KEY_T int
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

unsigned int num_elem;

struct elem {
	unsigned int height, size;
	KEY_T key;
	struct elem *left, *right;
} E[MAX_N];

unsigned int height(const struct elem *const e) {
	return e ? e->height : 0;
}

unsigned int size(const struct elem *const e) {
	return e ? e->size : 0;
}

int balance_factor(const struct elem *const e) {
	return e ? height(e->left) - height(e->right) : 0;
}

unsigned int update_height(struct elem *const e) {
	return e ? (e->height = MAX(height(e->left), height(e->right)) + 1) : 0;
}

unsigned int update_size(struct elem *const e) {
	return e ? (e->size = size(e->left) + size(e->right) + 1) : 0;
}

void update(struct elem *const e) {
	update_height(e), update_size(e);
}

struct elem * new_elem(const KEY_T key) {
	E[num_elem].key = key, E[num_elem].left = NULL, E[num_elem].right = NULL, E[num_elem].height = 1, E[num_elem].size = 1;
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

struct elem * min(struct elem *const e) {
	struct elem *m;
	if (!e) return NULL;
	for (m = e; m->left; m = m->left);
	return m;
}

struct elem * max(struct elem *const e) {
	struct elem *m;
	if (!e) return NULL;
	for (m = e; m->right; m = m->right);
	return m;
}

struct elem * ins(struct elem *const e, const KEY_T key) {
	int b;
	if (!e) return new_elem(key);
	if (e->key == key) return e;
	if (key < e->key) e->left = ins(e->left, key); else e->right = ins(e->right, key);
	update(e), b = balance_factor(e);
	return b > 1 && key < e->left->key ? zig(e) : b > 1 && key > e->left->key ? (e->left = zag(e->left), zig(e)) : b < -1 && key > e->right->key ? zag(e) : b < -1 && key < e->right->key ? (e->right = zig(e->right), zag(e)) : e;
}

struct elem * post_del(struct elem *const e) {
	int b;
	if (!e) return NULL;
	update(e), b = balance_factor(e);
	return b > 1 ? (balance_factor(e->left) >= 0 ? zig(e) : (e->left = zag(e->left), zig(e))) : b < -1 ? (balance_factor(e->right) <= 0 ? zag(e) : (e->right = zig(e->right), zag(e))) : e; 
}

struct elem * del(struct elem *const e, const KEY_T key) {
	struct elem *tmp, *_e;
	if (!e) return NULL;
	_e = e;
	if (key < e->key) e->left = del(e->left, key); else if (key > e->key) e->right = del(e->right, key); else if (e->left && e->right) e->right = del(e->right, e->key = min(e->right)->key); else {
		if (!(tmp = (e->left ? e->left : e->right))) tmp = e, _e = NULL; else *_e = *tmp;
		/* free(tmp); */
	}
	return post_del(_e);
}

struct elem * del_min(struct elem *const e) {
	struct elem *tmp, *_e;
	if (!e) return NULL;
	_e = e;
	if (e->left) e->left = del_min(e->left); else {
		if (!(tmp = e->right)) tmp = e, _e = NULL; else *_e = *tmp;
		/* free(tmp); */
	}
	return post_del(_e);
}

struct elem * del_max(struct elem *const e) {
	struct elem *tmp, *_e;
	if (!e) return NULL;
	_e = e;
	if (e->right) e->right = del_max(e->right); else {
		if (!(tmp = e->left)) tmp = e, _e = NULL; else *_e = *tmp;
		/* free(tmp); */
	}
	return post_del(_e);
}

struct elem * kth(struct elem *const e, const unsigned int k) {
	unsigned int ls;
	return ls = size(e->left), k < ls ? kth(e->left, k) : k == ls ? e : kth(e->right, k - ls - 1);
}

unsigned int count(struct elem *const e, const KEY_T key) {
	return !e ? 0 : e->key < key ? size(e->left) + 1 + count(e->right, key) : count(e->left, key);
}

void preorder(const struct elem *const e) {
	if (!e) return;
	printf("%d ", e->key), preorder(e->left), preorder(e->right);
}

int main(int argc, char *argv[]) {
	struct elem *e;
	e = ins(NULL, 9);
	e = ins(e, 5);
	e = ins(e, 10);
	e = ins(e, 0);
	e = ins(e, 6);
	e = ins(e, 11);
	e = ins(e, -1);
	e = ins(e, 1);
	e = ins(e, 2);
	preorder(e);
	printf("\n");
	e = del(e, 10);
	e = del(e, 13);
	preorder(e);
	printf("\n");
	return 0;
}
