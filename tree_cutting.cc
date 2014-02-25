#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX_N 10000

unsigned int dfs(const unsigned int N, const unsigned int n, unsigned int &num_s, bool visited[], unsigned int s[], const std::vector<unsigned int> adj[]) {
	bool suitable = true;
	unsigned int ss, subtree_size = 1;
	visited[n] = true;
	for (std::vector<unsigned int>::const_iterator iter = adj[n].begin(); iter != adj[n].end(); ++iter) {
		if (!visited[*iter]) {
			subtree_size += (ss = dfs(N, *iter, num_s, visited, s, adj));
			if (ss > (N >> 1)) suitable = false; 
		}
	}
	if (suitable) if (N - subtree_size <= (N >> 1)) s[num_s++] = n;
	return subtree_size;
}

int main(int argc, char *argv[]) {
	bool visited[MAX_N];
	unsigned int N, n, u, v, num_s = 0, s[MAX_N], subtree_size[MAX_N];
	std::vector<unsigned int> adj[MAX_N]; 
	scanf("%u", &N);
	for (n = 0; n < N; ++n) {
		subtree_size[n] = 1;
		visited[n] = false;
	}
	for (n = 0; n + 1 < N; ++n) {
		scanf("%u%u", &u, &v);
		--u;
		--v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(N, 0, num_s, visited, s, adj);
	if (num_s) {
		std::sort(s, s + num_s);
		for (n = 0; n < num_s; ++n) printf("%u\n", s[n] + 1);
	}else  printf("NONE\n");
	return 0;
}
