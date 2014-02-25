#include <iostream>
#include <set>

#define N 12

typedef struct node {
	int val;
	struct node *next;
} node;

void remove_loop(node * const root) {
	std::set<node *> s;
	node *ptr = root;
	while (true) {
		if (s.find(ptr -> next) != s.end()) {
			ptr -> next = NULL; 
			return;
		}
		s.insert(ptr);
		ptr = ptr -> next;
	}
}

bool linked_list_has_loop(node * const root, const bool remove_loop_if_exists = false) {
	node *ptr1 = root, *ptr2 = root;
	while (ptr2) {
		ptr2 = ptr2 -> next; 
		ptr1 = ptr1 -> next;
		if (ptr2) {
			ptr2 = ptr2 -> next;
			if (ptr2 == ptr1) {
				if (remove_loop_if_exists) {
					remove_loop(root);
				}
				return true;
			}
		}else {
			return false;
		}
	}
	return false;
}

void print_linked_list(const node * const root) {
	const node *ptr1 = root;
	while (ptr1) {
		std::cout << ptr1 -> val << " -> ";
		ptr1 = ptr1 -> next;
	}
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	node test0, test1, test2[N];
	test0.next = &test0;
	test1.next = NULL;
	for (unsigned int i = 0; i + 1 < N; ++i) {
		test2[i].next = &test2[i + 1];
	}
	test2[N - 1].next = NULL;
	std::cout << linked_list_has_loop(NULL) << std::endl;   /* false */
	std::cout << linked_list_has_loop(&test0) << std::endl; /* true */
	std::cout << linked_list_has_loop(&test1) << std::endl; /* false */
	std::cout << linked_list_has_loop(&test2[0]) << std::endl; /* false */
	for (unsigned int i = 0; i < N; ++i) {
		test2[i].val = i;
	}
	print_linked_list(&test2[0]);
	for (unsigned int i = N - 1; i >= 1; --i) {
		test2[N - 1].next = &test2[i];
		std::cout << linked_list_has_loop(&test2[0]) << std::endl; /* true */
	}
	std::cout << std::endl;
	for (unsigned int i = 0; i < N; ++i) {
		std::cout << std::endl;
		test2[N - 1].next = NULL;
		print_linked_list(&test2[0]);
		test2[N - 1].next = &test2[i];
		std::cout << linked_list_has_loop(&test2[0], true) << std::endl; /* true */
		print_linked_list(&test2[0]);
	}
	return 0;
}
