#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200        /* max number of candidate(s) */
#define MAX_M 20
#define MAX_SCORE 20     /* max score of each candidate ( in range [0, MAX_SCORE] ) */

int comp_candidate_num(const void *const a, const void *const b) {
	return *((const int *const)a) < *((const int *const)b) ? -1 : 1;
}

int main(int argc, char *argv[]) {
	unsigned int case_num = 0;
	int N, M, n, m, k, c, pm, pk, sum, diff, is_selected, abs_diff, opt_k, opt_abs_diff, opt_sum, SD, SP, D[MAX_N], P[MAX_N], J[MAX_M], feasible_sum[MAX_M + 1][(MAX_SCORE << 2) * MAX_M + 1], last_candidate[MAX_M + 1][(MAX_SCORE << 2) * MAX_M + 1];    /* 2nd dimension: diff + MAX_DIFF : [-MAX_DIFF, MAX_DIFF] -> [0, 2 * MAX_DIFF] */
	while (1) {
		scanf("%u%u", &N, &M); 
		if (!N && !M) return 0;
		for (m = 0; m <= M; ++m) for (k = 0; k <= (MAX_SCORE << 2) * MAX_M; ++k) feasible_sum[m][k] = -1;
		feasible_sum[0][(MAX_SCORE << 1) * MAX_M] = 0;
		last_candidate[0][0] = -1;
		for (n = 0; n < N; ++n) scanf("%u%u", &P[n], &D[n]);
		for (m = 1; m <= M; ++m)	{
			for (k = 0; k <= (MAX_SCORE << 2) * MAX_M; ++k) {
				if (feasible_sum[m - 1][k] == -1) continue;
				for (n = 0; n < N; ++n) {
					is_selected = 0; 
					pm = m - 1;
					pk = k; 
					while (pm) {
						if ((c = last_candidate[pm][pk]) == n) { is_selected = 1; break; }
						--pm;
						pk -= D[c] - P[c];
					}
					if (!is_selected) {
						diff = k + D[n] - P[n];
						if ((sum = feasible_sum[m - 1][k] + D[n] + P[n]) > feasible_sum[m][diff]) {
							feasible_sum[m][diff] = sum;
							last_candidate[m][diff] = n;
						}
					}
				}
			}
		}
		opt_k = 0;
		opt_abs_diff = (MAX_SCORE << 1) * MAX_M;  /* S(D) - S(P) == -(MAX_SCORE << 1) * MAX_M*/
		opt_sum = feasible_sum[M][0];
		for (k = 1; k <= (MAX_SCORE << 2) * MAX_M; ++k) {
			if (feasible_sum[M][k] != -1) {
				abs_diff = (k < (MAX_SCORE << 1) * MAX_M ? (MAX_SCORE << 1) * MAX_M - k : k - (MAX_SCORE << 1) * MAX_M);
				if (opt_sum == -1 || abs_diff < opt_abs_diff || (abs_diff == opt_abs_diff && feasible_sum[M][k] > opt_sum)) {
					opt_sum = feasible_sum[M][k];
					opt_k = k;
					opt_abs_diff = abs_diff;
				}
			}
		}
		SD = 0;
		SP = 0;
		pm = M;
		pk = opt_k;
		while (pm) {
			c = J[pm - 1] = last_candidate[pm][pk];	
			SD += D[c];
			SP += P[c];
			pk -= D[c] - P[c];
			--pm;
		}
		qsort(J, M, sizeof(int), comp_candidate_num);
		printf("Jury #%u\nBest jury has value %d for prosecution and value %d for defence:\n", ++case_num, SP, SD);
		for (m = 0; m < M; ++m) printf(" %d", J[m] + 1);
		printf("\n\n");
	}
	return 0;
}
