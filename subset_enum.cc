#include <iostream>

void subset_enum(const unsigned int n, const unsigned int k, const unsigned int A[]) {
	bool complete = false; 
	bool *current_subset = new bool[n];  
	for (unsigned int i = 0; i < n; ++i) {
		current_subset[i] = (i >= n - k);
	}
	while (true) {
		bool tmp;
		unsigned int z = n - 1, o = n - 1, s, e;
		for (unsigned int i = 0; i < n; ++i) {
			if (current_subset[i]) {
				std::cout << A[i] << ", ";
			}
		}
		std::cout << "\n";
		complete = true;
		for (unsigned int i = 0; i < k; ++i) {
			if (!current_subset[i]) {
				complete = false;
				break;
			}
		}
		if (complete) {
			break;
		}
		while (!current_subset[z]) {
			--z;
		}
		o = z;
		while (current_subset[o]) {
			--o;
		}
		current_subset[o] = true;
		current_subset[z] = false;
		s = o + 1;
		e = n - 1;
		while (s < e) {
			tmp = current_subset[s];
			current_subset[s] = current_subset[e];
			current_subset[e] = tmp;
			++s;
			--e;
		}
	}
	delete [] current_subset;
}

int main(int argc, char *argv[]) {
	unsigned int n, k, *A;
	std::cin >> n;
	std::cin >> k;   /* assume k <= n */
	A = new unsigned int[n];
	for (unsigned int i = 0; i < n; ++i) { 
		std::cin >> A[i];
	}
	subset_enum(n, k, A);
	return 0;
}
