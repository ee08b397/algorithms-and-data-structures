#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char *argv[]) {
	std::vector<int> s;
	s.push_back(3);
	s.push_back(1);
	s.push_back(4);
	s.push_back(5);
	s.push_back(9);
	s.push_back(7);
	std::sort(s.begin(), s.end()); 
	do {
		for (std::vector<int>::const_iterator iter = s.begin(); iter != s.end(); ++iter) {
			std::cout << *iter << ", ";
		}
		std::cout << std::endl;
	} while(next_permutation(s.begin(), s.end()));
	return 0;
}
