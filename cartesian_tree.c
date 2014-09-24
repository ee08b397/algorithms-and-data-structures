#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_N 1048576
#define NUM_DEL_TEST 100
#define KEY_MIN 1024
#define KEY_MAX 1048576
#define KEY_T int
#define PR_T int

static unsigned int num_node, key[MAX_N];

static struct node {
	KEY_T key;
	PR_T priority;
	struct node *left, *right, *parent;
} n[MAX_N], *root;

struct node * new_node(const KEY_T key, const PR_T priority) {
	n[num_node].key = key, n[num_node].priority = priority, n[num_node].left = NULL, n[num_node].right = NULL;
	return &n[num_node++];
}

void zig(struct node *const u) {
	struct node *l;
	l = u->left, l->parent = u->parent;
	if (u->parent) *(u == u->parent->left ? &(u->parent->left) : &(u->parent->right)) = l;
	if ((u->left = l->right)) u->left->parent = u;
	u->parent = l, l->right = u;
	if (u == root) root = l;
}

void zag(struct node *const u) {
	struct node *r;
	r = u->right, r->parent = u->parent;
	if (u->parent) *(u == u->parent->left ? &(u->parent->left) : &(u->parent->right)) = r;
	if ((u->right = r->left)) u->right->parent = u;
	u->parent = r, r->left = u;
	if (u == root) root = r;
}

void shift_up(struct node *const u) {
	while (u->parent && u->parent->priority > u->priority) if (u == u->parent->left) zig(u->parent); else zag(u->parent);
	if (!u->parent) root = u;
}

void shift_down(struct node *const u) {
	while (u->left || u->right) {
		if (!u->left) zag(u); else if (!u->right || u->left->priority < u->right->priority) zig(u); else zag(u);
		if (u == root) root = u->parent;
	}
}

void ins(struct node *const u) {
	struct node *p, **q;
	if (!root) { u->parent = NULL, root = u; return; }
	for (p = root; *(q = (u->key < p->key ? &(p->left) : &(p->right))); p = *q); 
	u->parent = p, shift_up(*q = u);
}

struct node * del(const KEY_T key) {
	struct node *u;
	for (u = root; u && key != u->key; u = (key < u->key ? u->left : u->right));
	if (!u) return NULL;
	shift_down(u), *(u == u->parent->left ? &(u->parent->left) : &(u->parent->right)) = NULL;
	return u;
}

void verify_inorder(const struct node *const u) {
	if (!u) return;
	verify_inorder(u->left), verify_inorder(u->right);
	if (u->left) assert(u->left->key <= u->key);
	if (u->right) assert(u->key <= u->right->key);
}

void verify_preorder(const struct node *const u) {
	if (!u) return;
	verify_preorder(u->left), verify_preorder(u->right);
	if (u->parent) assert(u->priority >= u->parent->priority);
}

int main(int argc, char *argv[]) {
	unsigned int n;
	struct node *u;
	for (srand(time(NULL)), num_node = 0; num_node < MAX_N; ins(new_node(key[num_node] = KEY_MIN + rand() % (KEY_MAX + 1 - KEY_MIN), rand())));
	verify_inorder(root), verify_preorder(root);
	for (n = 0; n < NUM_DEL_TEST; ++n) assert(!del(rand() % KEY_MIN)), assert(!del(KEY_MAX  + rand() % (KEY_MAX + 1 - KEY_MIN))), assert((u = del(key[n])) && key[n] == u->key), verify_inorder(root), verify_preorder(root);
	return 0;
}
