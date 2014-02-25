#include <iostream>
#include <list>
#include <cmath> 

bool subset_sum(const int sum, const size_t N, const int *a, const size_t current_idx, std::list<size_t> & elem_idx) {
	if (sum == 0) {
		return true;
	}
	size_t idx = current_idx;
	while (idx < N) {
		elem_idx.push_back(idx);
		if (subset_sum(sum - a[idx], N, a, idx + 1, elem_idx)) {
			return true;
		}
		elem_idx.pop_back();
		++idx;
	}
	return false;
}

int main(int argc, char *argv[]) {
	size_t N, idx = 0;
	int sum = 0, diff = 0, sgn, *a;
	std::cin >> N;
	std::list<size_t> elem_idx, second_set_elem_idx;
	a = new int[N];
	for (size_t n = 0; n < N; ++n) {
		std::cin >> a[n];
		sum += a[n];
	}
	sgn = sum > 0 ? 1 : -1;  
	while (diff <= sgn * sum / 2 && !subset_sum(sum / 2 - diff, N, a, 0, elem_idx)) {
		++diff;
	}
	std::cout << "balanced partition: {";
	for (std::list<size_t>::const_iterator iter = elem_idx.begin(); iter != elem_idx.end(); ++iter) {
		while (idx != *iter) {
			second_set_elem_idx.push_back(idx);
			++idx;
		}
		++idx;
		std::cout << a[*iter] << ",";
	}
	while (idx < N) {
		second_set_elem_idx.push_back(idx);
		++idx;
	}
	std::cout << "}, {";
	for (std::list<size_t>::const_iterator s_iter = second_set_elem_idx.begin(); s_iter != second_set_elem_idx.end(); ++s_iter) {
		std::cout << a[*s_iter] << ",";
	}
	std::cout << "}\n";
	std::cout << "difference: " << ((sum - sum / 2 + diff) - (sum / 2 - diff)) << "\n";
	delete [] a;
	return 0;
}
