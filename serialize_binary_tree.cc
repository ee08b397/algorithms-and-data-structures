#include <iostream>
#include <fstream>
#include <string>
#include <stack>

struct node {
	unsigned int value;
	struct node *left;
	struct node *right;
	node(unsigned int __value = 0) {
		value = __value;
		left = NULL;
		right = NULL;
	}
};

class binary_tree_util {
	public :
		static void print_binary_tree(const size_t level, const struct node * const root) {
			if (root) {
				for (size_t l = 0; l <= level; ++l) {
					std::cout << "| ";
				}
				std::cout << "\n";
				for (size_t l = 0; l < level; ++l) {
					std::cout << "| ";
				}
				std::cout << "|_";
				std::cout << root -> value << "\n";
				print_binary_tree(level + 1, root -> left);
				print_binary_tree(level + 1, root -> right);
			}
		}
		static void serialize_binary_tree(const std::string filename, const struct node * const root) {
			std::ofstream fp(filename.c_str(), std::ios::trunc | std::ios::binary);
			std::stack<const struct node *> s;
			s.push(root);
			while (!s.empty()) {
				const struct node *ptr = s.top();
				s.pop();
				if (ptr) {
					fp << NON_EMPTY_NODE;	
					fp << ptr -> value;
					s.push(ptr -> right); 
					s.push(ptr -> left); 
				}else {
					fp << EMPTY_NODE;		
				}
			}
			fp.close();
		}
		static struct node * deserialize_binary_tree(const std::string filename) {
			char c;
			unsigned int value;
			std::ifstream fp(filename.c_str(), std::ios::binary); 
			struct node * root;// = NULL;//, *ptr = root, *left, *right;
			std::stack<struct node **> s;
			s.push(&root);
			while (!fp.eof() && !s.empty()) {
				struct node ** ptr = s.top(); 
				s.pop();
				fp >> c;
				if (c == NON_EMPTY_NODE) {
					fp >> value;
					*ptr = new node(value);
					s.push(&((*ptr) -> right));
					s.push(&((*ptr) -> left));
				}else {
					*ptr = NULL;
				}
			}
			fp.close();
			return root;
		}
		static void delete_binary_tree(const struct node * const root) {
			if (root) {
				delete_binary_tree(root -> left);
				delete_binary_tree(root -> right);
				delete root;
			}
		}
	private : 
		const static char EMPTY_NODE = '\0';
		const static char NON_EMPTY_NODE = '\1';
};

int main(int argc, char *argv[]) {
	struct node T[8], singleton, *result;
	for (size_t n = 0; n < 8; ++n) {
		T[n].value = n;
	}
	T[0].left = &T[1];
	T[0].right = &T[2];
	T[1].left = &T[3];
	T[1].right = &T[4];
	T[4].left = &T[5];
	T[4].right = &T[6];
	T[2].left = &T[7];
	singleton.value = 99;
	binary_tree_util::print_binary_tree(0, &T[0]);
	std::cout << "\nserializing binary tree...\n" << std::endl;
	binary_tree_util::serialize_binary_tree(".serialized_binary_tree", &T[0]);
	std::cout << "deserializing binary tree..." << std::endl;
	result = binary_tree_util::deserialize_binary_tree(".serialized_binary_tree");
	binary_tree_util::print_binary_tree(0, result);
	binary_tree_util::delete_binary_tree(result);

	std::cout << std::endl;

	binary_tree_util::serialize_binary_tree(".serialized_empty_binary_tree", NULL);
	result = binary_tree_util::deserialize_binary_tree(".serialized_empty_binary_tree");
	binary_tree_util::print_binary_tree(0, result);
	binary_tree_util::delete_binary_tree(result);

	binary_tree_util::serialize_binary_tree(".serialized_singleton_binary_tree", &singleton);
	result = binary_tree_util::deserialize_binary_tree(".serialized_singleton_binary_tree");
	binary_tree_util::print_binary_tree(0, result);
	binary_tree_util::delete_binary_tree(result);

	return 0;
}
