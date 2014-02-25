#include <cstdio>
#include <list>
#include <stack>

#define MAX_N 10000
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/* Tarjan's strongly connected component algorithm */
void compute_scc(const unsigned int v, unsigned int &current_index, unsigned int &num_scc, unsigned int index[], unsigned int low_link[], bool in_S[], const std::list<unsigned int> adj[], std::stack<unsigned int> &S, unsigned int scc_n[], unsigned int scc_size[]) {
	low_link[v] = index[v] = current_index++;
	S.push(v);
	in_S[v] = true;
	for (std::list<unsigned int>::const_iterator iter = adj[v].begin(); iter != adj[v].end(); ++iter) {
		if (index[*iter] == MAX_N) {
			compute_scc(*iter, current_index, num_scc, index, low_link, in_S, adj, S, scc_n, scc_size);
			low_link[v] = std::min(low_link[v], low_link[*iter]);
		}else if (in_S[*iter]) low_link[v] = std::min(low_link[v], index[*iter]);
	}
	if (low_link[v] == index[v]) {
		scc_size[num_scc] = 0;
		unsigned int w = v;
		do {
			w = S.top();
			S.pop();
			in_S[w] = false;
			scc_n[w] = num_scc;
			++scc_size[num_scc];
		} while (w != v);
		++num_scc;
	}
}

int main(int argc, char *argv[]) {
	unsigned int N, M, A, B, n, num_scc, current_index, w, ans, num_scc_zero_out_deg, index[MAX_N], low_link[MAX_N], scc_n[MAX_N], scc_size[MAX_N];
	bool in_S[MAX_N], scc_zero_out_deg[MAX_N];
	std::stack<unsigned int> S; 
	std::list<unsigned int> adj[MAX_N];
	scanf("%u%u", &N, &M);
	while (M--) {
		scanf("%u%u", &A, &B); 
		adj[--A].push_back(--B);
	}
	current_index = 0;
	for (n = 0; n < N; ++n) {
		index[n] = MAX_N;
		in_S[n] = false;
	}
	num_scc = 0;
	current_index = 0; 
	for (n = 0; n < N; ++n) if (index[n] == MAX_N) compute_scc(n, current_index, num_scc, index, low_link, in_S, adj, S, scc_n, scc_size);
	for (n = 0; n < num_scc; ++n) scc_zero_out_deg[n] = true;
	num_scc_zero_out_deg = num_scc;
	ans = 0;
	for (n = 0; n < N; ++n) {
		w = scc_n[n];
		if (scc_zero_out_deg[w]) {
			for (std::list<unsigned int>::const_iterator iter = adj[n].begin(); iter != adj[n].end(); ++iter) {
				if (scc_n[*iter] != w) {
					scc_zero_out_deg[w] = false;
					--num_scc_zero_out_deg;
					break;
				}
			}
			if (scc_zero_out_deg[w]) {
				ans = scc_size[w];
			}
		}
	}
	if (num_scc_zero_out_deg > 1) printf("0\n"); else printf("%u\n", ans);
	return 0;
}
