#include <iostream>
#include <stack>
#include <queue>

class node {

	private: 
		size_t N;
		node **chld;

	public:
		node() : N(0), chld(NULL) {}

		node(const size_t __N) : N(__N), chld(new node*[N]) {
			for (size_t i = 0; i < N; ++i) {
				chld[i] = NULL;
			}
		}

		void set_chld(const size_t n, node * const c) {
			chld[n] = c;
		}

		~node() {
			if (chld != NULL) {
				delete [] chld;
			}
		}

		size_t get_num_chld() const {
			return N;
		}

		const node* get_chld(size_t n) const {
			return (const node*)chld[n];
		}

		bool is_symmetric() const {
			std::stack<const node*> s;
			s.push(this);
			while (!s.empty()) {
				size_t nc;
				const node *current_node = s.top();
				s.pop();
				nc = current_node -> get_num_chld(); 
				for (size_t i = 0; i < nc / 2; ++i) { 
					if (i != nc - 1 - i) {
						if (!is_isomorphic(current_node -> get_chld(i), current_node -> get_chld(nc - 1 - i))) {
							return false;
						}
					}else {
						s.push(current_node -> get_chld(i));
					}
				}
			}
			return true;
		}

		static bool is_isomorphic(const node *n1, const node *n2) {
			std::queue< std::pair<const node*, const node*> > q;			
			q.push(std::pair<const node*, const node*>(n1, n2)); 
			while (!q.empty()) {
				size_t nc;
				std::pair<const node*, const node*> p = q.front();
				q.pop();
				if (p.first == p.second) {
					continue;
				}else if ((p.first == NULL && p.second != NULL) || (p.first != NULL && p.second == NULL)) {
					return false;
				}else {
					nc = p.first -> get_num_chld();
					if (nc != p.second -> get_num_chld()) {
						return false;
					}
					for (size_t n = 0; n < nc; ++n) {
						q.push(std::pair<const node*, const node*>(p.first -> get_chld(n), p.second -> get_chld(n)));
					}
				}
			}
			return true;
		}

};

int main(int argc, char *argv[]) {
	node *test0 = new node(), *test1 = new node(2), *test1_c0 = new node(), *test1_c1 = new node();
	std::cout << test0 -> is_symmetric() << "\n";   // 1
	test1 -> set_chld(0, test1_c0);
	std::cout << test1 -> is_symmetric() << "\n";   // 0
	test1 -> set_chld(1, test1_c0);
	std::cout << test1 -> is_symmetric() << "\n";   // 1
	test1 -> set_chld(1, test1_c1);
	std::cout << test1 -> is_symmetric() << "\n";   // 1
	test1 -> set_chld(1, test1);
	std::cout << test1 -> is_symmetric() << "\n";   // 0
	test1 -> set_chld(0, test1);
	std::cout << test1 -> is_symmetric() << "\n";   // 1
	test1 -> set_chld(1, test0);
	std::cout << test1 -> is_symmetric() << "\n";   // 0
	delete test0;
	delete test1;
	delete test1_c0;
	delete test1_c1;
	return 0;
}
