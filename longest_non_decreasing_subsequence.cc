#include <iostream>
#include <climits>
#include <map>
#include <cassert>

size_t longest_non_decreasing_subsequence(const int current_max, const size_t next_idx, const size_t N, const int *a, std::map< std::pair<size_t, int>, bool > &incl, std::map< std::pair<size_t, int>, size_t > &len) {
	if (next_idx == N) {
		return 0;
	}
	std::map< std::pair<size_t, int>, size_t >::const_iterator l_iter = len.find(std::pair<size_t, int>(next_idx, current_max));
	if (l_iter != len.end()) {
		return l_iter -> second;
	}
	size_t l1 = longest_non_decreasing_subsequence(current_max, next_idx + 1, N, a, incl, len);
	if (a[next_idx] >= current_max) {
		size_t l2 = 1 + longest_non_decreasing_subsequence(a[next_idx], next_idx + 1, N, a, incl, len);
		if (l2 > l1) {
			incl.insert(std::pair< std::pair<size_t, int>, bool>(std::pair<size_t, int>(next_idx, current_max), true));
			len.insert(std::pair< std::pair<size_t, int>, size_t>(std::pair<size_t, int>(next_idx, current_max), l2));
			return l2;
		}
		incl.insert(std::pair< std::pair<size_t, int>, bool>(std::pair<size_t, int>(next_idx, current_max), false));
	}
	len.insert(std::pair< std::pair<size_t, int>, size_t>(std::pair<size_t, int>(next_idx, current_max), l1));
	return l1;
}

int main(int argc, char *argv[]) {
	size_t N;
	int current_max = INT_MIN, *a;
	std::map< std::pair<size_t, int>, bool > incl;
	std::map< std::pair<size_t, int>, size_t > len;
	std::cin >> N;
	a = new int[N];
	for (size_t n = 0; n < N; ++n) {
		std::cin >> a[n];
	}
	std::cout << "length of longest non-decreasing subsequence: " << longest_non_decreasing_subsequence(INT_MIN, 0, N, a, incl, len) << std::endl;
	std::cout << "a longest non-decreasing subsequence: \n"; 
	for (size_t i = 0; i < N; ++i) {
		if (a[i] < current_max) {
			continue;
		}
		std::map< std::pair<size_t, int>, bool >::const_iterator iter = incl.find(std::pair<size_t, int>(i, current_max));
		assert(iter != incl.end());	
		if (iter -> second) {
			current_max = a[i];
			std::cout << a[i] << ",";
		}
	}
	std::cout << "\n";
	delete [] a;
	return 0;
}
