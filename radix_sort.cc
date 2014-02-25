#include <iostream>
#include <list>

int main(int argc, char *argv[]) {
	size_t N;
	unsigned int n;
	std::list<unsigned int> b[4];
	std::cin >> N;
	for (size_t i = 0; i < N; ++i) {
		std::cin >> n;
		b[n & 1].push_back(n);
	}
	for (unsigned int i = 1; i < (sizeof(unsigned int) << 3); ++i) {
		unsigned int p = (i & 1) << 1, np = ((~i & 1)) << 1;
		b[p].clear(); 
		b[p + 1].clear(); 
		for (std::list<unsigned int>::const_iterator iter = b[np].begin(); iter != b[np].end(); ++iter) {
			b[p + (((*iter) >> i) & 1)].push_back(*iter);
		}
		for (std::list<unsigned int>::const_iterator iter = b[np + 1].begin(); iter != b[np + 1].end(); ++iter) {
			b[p + (((*iter) >> i) & 1)].push_back(*iter);
		}
		if (i + 1 == (sizeof(int) << 3)) {
			for (std::list<unsigned int>::const_iterator iter = b[p].begin(); iter != b[p].end(); ++iter) {
				std::cout << *iter << ", ";
			}
			for (std::list<unsigned int>::const_iterator iter = b[p + 1].begin(); iter != b[p + 1].end(); ++iter) {
				std::cout << *iter << ", ";
			}
			std::cout << std::endl;
		}
	}
	return 0;
}
