#include <iostream>
#include <stack>

typedef struct node {
	unsigned int value;
	struct node *left, *right;
} node;

void alternating_order_bfs(const node *root) {
	bool reverse = false;
	std::stack<const node *> s, s_r;
	s.push(root);
	while (!s.empty() || !s_r.empty()) {
		if (reverse) {
			while (!s_r.empty()) {
				const node *elem = s_r.top();
				s_r.pop();
				std::cout << elem -> value << " ";
				if (elem -> right) {
					s.push(elem -> right);
				}
				if (elem -> left) {
					s.push(elem -> left);
				}
			}
		}else {
			while (!s.empty()) {
				const node *elem = s.top();
				s.pop();
				std::cout << elem -> value << " ";
				if (elem -> left) {
					s_r.push(elem -> left);
				}
				if (elem -> right) {
					s_r.push(elem -> right);
				}
			}
		}
		reverse = !reverse;
	}
}

/*
               1
        2           3 
     4    5      6     7
           8    9 10    11
         12 13 14
 */

int main(int argc, char *argv[]) {
	node n[14];
	for (size_t i = 0; i < 14; ++i) {
		n[i].value = i + 1;
	}
	n[0].left = &n[1];
	n[0].right = &n[2];
	n[1].left = &n[3];
	n[1].right = &n[4];
	n[2].left = &n[5];
	n[2].right = &n[6];
	n[3].left = NULL;
	n[3].right = NULL;
	n[4].left = &n[7];
	n[4].right = NULL;
	n[5].left = &n[8];
	n[5].right = &n[9];
	n[6].left = NULL;
	n[6].right = &n[10];
	n[7].left = &n[11];
	n[7].right = &n[12];
	n[8].left = &n[13];
	n[8].right = NULL;
	for (size_t i = 9; i < 14; ++i) {
		n[i].left = NULL;
		n[i].right = NULL;
	}
	alternating_order_bfs((const node *)&n[0]);
	return 0;
}
