#include <iostream>
#include <climits>

int main(int argc, char *argv[]) {
	size_t N, start = 0, end = 0, max_start = 0, max_end = 0; 
	long current_sum, max_sum, *a;
	std::cin >> N;
	if (N > 0) {
		a = new long[N];
		for (size_t i = 0; i < N; ++i) {
			std::cin >> a[i];
		}
		current_sum = a[0];
		max_sum = a[0];
		for (size_t i = 1; i < N; ++i) {
			if (current_sum < 0) {
				start = i;
				current_sum = a[i];
			}else {
				current_sum += a[i];
			}
			end = i;
			if (current_sum > max_sum) {
				max_start = start;
				max_end = end;
				max_sum = current_sum;
			}
		}
		std::cout << max_start << " , " << max_end << " , " << max_sum << "\n";
		delete [] a;
	}
	return 0;
}
