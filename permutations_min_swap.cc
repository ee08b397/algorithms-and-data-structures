#include <iostream>
#include <list>

int main(int argc, char *argv[]) {
	unsigned int N = 0;
	std::list<unsigned int *> perms;
	std::cin >> N;
	if (N > 0) {
		unsigned int *p = new unsigned int[N];
		for (unsigned int i = 0; i < N; ++i) {
			p[i] = i;
		}
		perms.push_back(p);
		for (unsigned int i = 0; i + 1 < N; ++i) {
			size_t n = perms.size();
			std::list<unsigned int *>::const_iterator p_iter = perms.begin();
			for (unsigned int k = 0; k < n; ++k, ++p_iter) {
				for (unsigned int j = i + 1; j < N; ++j) {
					const unsigned int *cp = *p_iter;
					unsigned int *np = new unsigned int[N];
					for (unsigned int l = 0; l < N; ++l) {
						np[l] = l == i ? cp[j] : l == j ? cp[i] : cp[l];
					}
					perms.push_back(np);
				}
			}
		}
		for (std::list<unsigned int *>::const_iterator p_iter = perms.begin(); p_iter != perms.end(); ++p_iter) {
			for (unsigned int i = 0; i < N; ++i) {
				std::cout << (*p_iter)[i] << ",";
			}
			std::cout << "\n";
			delete [] (*p_iter);
		}
	}
	return 0;		
}
