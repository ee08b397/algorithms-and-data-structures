#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX_N 4000

int v[4][MAX_N], sum[MAX_N * MAX_N];

int main(int argc, char *argv[]) {
	unsigned int N, i, j, sum_idx;
	unsigned long num_tuples;
	std::pair<int*, int*> r;
	scanf("%u", &N);
	for(i = 0; i < N; ++i) for(j = 0; j < 4; ++j) scanf("%d", &v[j][i]);
	for (j = 0; j < 4; ++j) std::sort(v[j], v[j] + N);
	for(sum_idx = 0, i = 0; i < N; ++i) for(j = 0; j < N; ++j) sum[sum_idx++] = v[0][i] + v[1][j];
	std::sort(sum, sum + sum_idx);
	for(num_tuples = 0, i = 0; i < N; ++i) for(j = 0; j < N; ++j) r = std::equal_range(sum, sum + sum_idx, -(v[2][i] + v[3][j])), num_tuples += r.second - r.first;
	printf("%lu\n", num_tuples);
	return 0;
}
