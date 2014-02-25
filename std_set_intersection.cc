#include <iostream>
#include <algorithm>
#include <vector>

#define SIZE_OF_FIRST_SET 10
#define SIZE_OF_SECOND_SET 8

int main (int argc, char *argv[]) {
	int first[] = {1, 2, 4, 5, 9, 10, 11, 15, 20, 25};
	int second[] = {2, 3, 4, 50, 40, 30, 20, 10};
	std::vector<int> v(std::max(SIZE_OF_FIRST_SET, SIZE_OF_SECOND_SET));
	std::vector<int>::iterator it;
	std::sort (first, first + SIZE_OF_FIRST_SET);
	std::sort (second, second + SIZE_OF_SECOND_SET);
	it = std::set_intersection(first, first + SIZE_OF_FIRST_SET, second, second + SIZE_OF_SECOND_SET, v.begin());
	v.resize(it - v.begin());
	std::cout << "The intersection has " << (v.size()) << " elements:\n";
	for (it = v.begin(); it != v.end(); ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << '\n';
	return 0;
}
