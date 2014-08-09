#include <iostream>

int main(int argc, char *argv[]) {
	unsigned int N = 0;
	std::cin >> N;
	if (N > 0) {
		unsigned int *p = new unsigned int[N];
		for (unsigned int i = 0; i < N; ++i) {
			p[i] = i;
		}
		while (true) {
			unsigned int s = N - 1, t = N - 1, temp;
			for (unsigned int i = 0; i < N; ++i) {
				std::cout << p[i] << " ";
			}
			std::cout << "\n";
			while (s > 0) {
				if (p[s - 1] < p[s]) {
					break;
				}
				--s;
			}
			if (s == 0) {
				break;
			}
			while (p[t] <= p[s - 1]) {
				--t;
			}
			temp = p[t];
			p[t] = p[s - 1];
			p[s - 1] = temp;
			for (unsigned int r = 0; s + r < N - 1 - r; ++r) {
				temp = p[s + r];
				p[s + r] = p[N - 1 - r];
				p[N - 1 - r] = temp;
			}
		}
		delete [] p; 
	}
	return 0;
}
