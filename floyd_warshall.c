#include <stdio.h>
#include <limits.h>

#define MAX_N 100
#define INF 1001

int main(int argc, char *argv[]) {
	unsigned short N, D, d, l, i, j, k, alt, fp, max_dist, min_max_dist, dist[MAX_N][MAX_N];
	while (1) {
		scanf("%hu", &N);
		if (!N) return 0;
		for (i = 0; i < N; ++i) for (j = 0; j < N; ++j) dist[i][j] = (i == j ? 0 : INF);  
		for (i = 0; i < N; ++i) {
			scanf("%hu", &D);
			for (d = 0; d < D; ++d) {
				scanf("%hu%hu", &j, &l); 
				dist[i][--j] = l;
			}
		}
		for (k = 0; k < N; ++k) for (j = 0; j < N; ++j) for (i = 0; i < N; ++i) if (dist[i][j] > (alt = dist[i][k] + dist[k][j])) dist[i][j] = alt;
		for (min_max_dist = INF, fp = INF, i = 0; i < N; ++i) {
			for (max_dist = 0, j = 0; j < N; ++j) if (j != i && dist[i][j] > max_dist) max_dist = dist[i][j];  
			if (max_dist < min_max_dist) min_max_dist = max_dist, fp = i; 
		}
		if (min_max_dist == INF) printf("disjoint\n"); else printf("%hu %hu\n", fp + 1, min_max_dist);
	}
	return 0;
}
