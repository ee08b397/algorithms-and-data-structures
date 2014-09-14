#include <stdio.h>

#define MAX_N 200000
#define MAX_QLEN 4
#define INS 'I'
#define DEL 'D'
#define KTH 'K'
#define CNT 'C'
#define INVALID "invalid\n"
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
	for (m = e; m->left; m = m->left);
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

struct elem * del(struct elem *const e, const KEY_T key) {
	int b;
	struct elem *tmp, *_e;
	if (!e) return NULL;
	_e = e;
	if (key < e->key) e->left = del(e->left, key); else if (key > e->key) e->right = del(e->right, key); else if (e->left && e->right) e->right = del(e->right, e->key = min(e->right)->key); else {
		if (!(tmp = (e->left ? e->left : e->right))) tmp = e, _e = NULL; else *_e = *tmp;
		/* free(tmp); */
	}
	if (!_e) return NULL;
	update(_e), b = balance_factor(_e);
	return b > 1 ? (balance_factor(_e->left) >= 0 ? zig(_e) : (_e->left = zag(_e->left), zig(_e))) : b < -1 ? (balance_factor(_e->right) <= 0 ? zag(_e) : (_e->right = zig(_e->right), zag(_e))) : _e; 
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
	unsigned int Q, K;
	KEY_T key;
	char q[MAX_QLEN + 1];
	struct elem *e;
	scanf("%u", &Q);
	e = NULL, num_elem = 0;
	while (Q--) {
		scanf("%s", q);
		if (INS == q[0]) {
			scanf("%d", &key);
			e = ins(e, key);
		}else if (DEL == q[0]) {
			scanf("%d", &key);
			e = del(e, key);
		}else if (KTH == q[0]) {
			scanf("%u", &K);
			if (K > size(e)) printf(INVALID); else printf("%d\n", kth(e, K - 1)->key);
		}else if (CNT == q[0]) {
			scanf("%d", &key);
			printf("%u\n", count(e, key));
		}
	}
	return 0;
}
