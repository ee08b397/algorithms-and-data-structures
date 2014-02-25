#include <cstdio>
#include <cstring>
#include <utility>
  
#define MAX_N 1001
#define MAX_M 100000
#define P_TYPE 'P'
#define V_TYPE 'V'

/* optimized Bellman-Ford algorithm for negative cycle detection */  
bool is_reliable(const unsigned int V, const unsigned int E, const std::pair<int, int> edge[], const int w[], int dist[]) { 
	bool path_shortened = false;
	int d;
	memset(dist, 0, sizeof(dist));
	for (unsigned int v = 0; v < V; ++v) {
		path_shortened = false;
		for (unsigned int e = 0; e < E; ++e) {
	        	if (dist[edge[e].second] > (d = dist[edge[e].first] - w[e])) {  
				dist[edge[e].second] = d;
				path_shortened = true;
			}
		}
		if(!path_shortened) break;   /* no path is shortened within current iteration => no path will be shortened in subsequent iteration(s) */
	}
	return !path_shortened;	
}

int main(int argc, char *argv[]) {  
	unsigned int N, M, m;
	int w[(MAX_M << 1) + 1];  /* edge weights */
	int dist[MAX_N];   /* distance from source */
	std::pair<int, int> edge[(MAX_M << 1) + 1];   /* edge end points */
	while (scanf("%u%u", &N, &M) != EOF) {
		/* printf("N == %u, M == %u\n", N, M); */
		int e_idx = 0;
		for (m = 0; m < M; ++m) {
			char t;
			int A, B, X;
			getchar();
			scanf("%c", &t);
			if(t == P_TYPE) {  
				scanf("%d%d%d", &A, &B, &X);  
				/* printf("A == %d, B == %d, X == %d\n", A, B, X); */
				edge[e_idx].first = A;  
				edge[e_idx].second = B;  
				w[e_idx++] = X;
				edge[e_idx].first = B;  
				edge[e_idx].second = A;  
				w[e_idx++] = -X;
			}else if (t == V_TYPE) {  
				scanf("%d%d", &edge[e_idx].first, &edge[e_idx].second);
				/* printf("A == %d, B == %d\n", edge[e_idx].first, edge[e_idx].second); */
				w[e_idx++] = 1;  
			}
		}
		printf(is_reliable(N, e_idx, edge, w, dist) ? "Reliable\n" : "Unreliable\n");
	}
	return 0;
}
