#include <iostream>
#include <cstring>
#include <stack>

void find_cycle(const unsigned int N, const unsigned int **adj) {
	unsigned int *state;
	std::stack<unsigned int> s;
	if (N == 0) {
		return;
	}
	state = new unsigned int[N];
	memset(state, 0, N * sizeof(unsigned int));
	for (unsigned int n = 0; n < N; ++n) {
		if (state[n] == 0) {
			s.push(n + 1);
			while (!s.empty()) {
				unsigned int v;
				v = s.top();
				if (state[v - 1] == 0) {
					unsigned int idx = 0;
					state[v - 1] = 1;
					while (idx < N && adj[v - 1][idx]) {
						if (state[adj[v - 1][idx] - 1] == 0) {  
							s.push(adj[v - 1][idx]);
						}else if (state[adj[v - 1][idx] - 1] == 1) {
							std::cerr << "found cycle" << std::endl; 
							return;
						}
						++idx;
					}
				}else if (state[v - 1] == 1) {
					state[v - 1] = 2;
					s.pop();
				}
			}
		}
	}
	std::cout << "no cycle was found" << std::endl;
	delete [] state;
}

int main(int argc, char *argv[]) {
	unsigned int N, u, v, *adj_size, **adj;
	std::cin >> N;
	adj = new unsigned int*[N];
	adj_size = new unsigned int[N];
	memset(adj_size, 0, N * sizeof(unsigned int));
	for (unsigned int n = 0; n < N; ++n) {   /* vertices are numbered [1 .. N], 0 denotes end of list of adjacent vertices */
		adj[n] = new unsigned int[N];
		memset(adj[n], 0, N * sizeof(unsigned int));
	}
	while (std::cin >> u >> v) {
		if (u >= 1 && u <= N && v >= 1 && v <= N) {
			adj[u - 1][adj_size[u - 1]++] = v; 
		}else {
			std::cerr << "input is outside the allowed range" << std::endl;
		}
	}
	find_cycle(N, (const unsigned int **)adj);
	for (unsigned int n = 0; n < N; ++n) {
		delete [] adj[n];
	}
	delete [] adj;
	delete [] adj_size;
	return 0;
}
