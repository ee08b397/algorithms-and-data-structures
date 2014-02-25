#include <stdio.h>
#include <string.h>

#define MAX_N 200
// M is number of applicants and N is number of jobs
/*
#define M 6
#define N 6
*/
 
/* A DFS based recursive function that returns true if a matching for vertex u is possible */
unsigned int bpm(const unsigned int N, const unsigned int bpGraph[][MAX_N], const unsigned int u, int seen[], int matchR[]) {
    /* Try every job one by one */
	int v;
	for (v = 0; v < N; v++) {
        /* If applicant u is interested in job v and v is not visited */
        	if (bpGraph[u][v] && !seen[v]) {
			seen[v] = 1; /* Mark v as visited */
			/*
			If job 'v' is not assigned to an applicant OR previously assigned applicant for job v (which is matchR[v])
			has an alternate job available. Since v is marked as visited in the above line, matchR[v] in the following
			recursive call will not get job 'v' again
			*/
			if (matchR[v] < 0 || bpm(N, bpGraph, matchR[v], seen, matchR)) {
				matchR[v] = u;
				return 1;
			}
		}
	}
	return 0;
}
 
/* Returns maximum number of matching from M to N */
unsigned int maxBPM(const unsigned int M, const unsigned int N, const unsigned int bpGraph[][MAX_N]) {
	/*
	An array to keep track of the applicants assigned to jobs. The value of matchR[i] is the applicant number
	assigned to job i, the value -1 indicates nobody is assigned.
	*/
	unsigned int u, result = 0; /* Count of jobs assigned to applicants */
	int matchR[N], seen[N];
	/* Initially all jobs are available */
	memset(matchR, -1, sizeof(matchR));
	for (u = 0; u < M; ++u) {
        /* Mark all jobs as not seen for next applicant. */
		memset(seen, 0, sizeof(seen));
        /* Find if the applicant 'u' can get a job */
		if (bpm(N, bpGraph, u, seen, matchR)) ++result;
	}
	return result;
}
 
int main(int argc, char *argv[]) {
	unsigned int c, G, B, M, g, b, bpGraph[MAX_N][MAX_N];
	c = 0;
	while (1) {
		scanf("%u%u%u", &G, &B, &M);
		if (!G && !B && !M) {
			return 0;
		}
		++c;
		for (g = 0; g < G; ++g) {
			for (b = 0; b < B; ++b) {
				bpGraph[g][b] = 1;
			}
		}
		while (M--) {
			scanf("%u%u", &g, &b);
				bpGraph[g - 1][b - 1] = 0; 
		}
		printf("Case %u: %u\n", c, G + B - maxBPM(G, B, (const unsigned int(*)[MAX_N])bpGraph));
	}
	return 0;
}
