#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 40000
#define MAX_NUM_NODE 262144 

struct bldg{ 
	unsigned int A, B, H;
};

struct region {
	unsigned int H, pd;
	unsigned long long area;
};

unsigned int N, cnt, disc[MAX_N << 1];
struct bldg b[MAX_N];
struct region t[MAX_NUM_NODE];

int cmp(const void *const a, const void *const b) {
	return *((const unsigned int *const)a) < *((const unsigned int *const)b) ? -1 : 1;
}

int cmp_by_h(const void *const a, const void *const b) {
	return ((const struct bldg *const)a) -> H < ((const struct bldg *const)b) -> H ? -1 : 1;
}

unsigned int find_idx(const unsigned int H) {
	unsigned int min = 0, max = cnt - 1, mid; 
	while (min <= max) {
		mid = (min + max) >> 1; 
		if (H < disc[mid]) max = mid - 1; 
		else if (H > disc[mid]) min = mid + 1; 
		else return mid;
	}
	return -1;
}

void init(const unsigned int node_num, const unsigned int min_idx, const unsigned int max_idx) {
	unsigned int mid_idx;
	t[node_num - 1].H = 0, t[node_num - 1].area = 0, t[node_num - 1].pd = 0; 
	if (max_idx > min_idx + 1) mid_idx = (min_idx + max_idx) >> 1, init(node_num << 1, min_idx, mid_idx), init((node_num << 1) | 1, mid_idx, max_idx);
}

void push_down(const unsigned int node_num, const unsigned int min_idx, const unsigned int max_idx) {
	unsigned int mid_idx, l_node_num, r_node_num;
	if (t[node_num - 1].pd) mid_idx = (min_idx + max_idx) >> 1, l_node_num = node_num << 1, r_node_num = l_node_num | 1, t[l_node_num - 1].area = ((unsigned long long)(t[l_node_num - 1].H = t[node_num - 1].H)) * (disc[mid_idx] - disc[min_idx]), t[r_node_num - 1].area = ((unsigned long long)(t[r_node_num - 1].H = t[node_num - 1].H)) * (disc[max_idx] - disc[mid_idx]), t[node_num - 1].pd = 0, t[l_node_num - 1].pd = 1, t[r_node_num - 1].pd = 1;
}

void update(const unsigned int node_num, const unsigned int min_idx, const unsigned int max_idx, const unsigned int start, const unsigned int end, const unsigned int H) {
	unsigned int mid_idx, l_node_num, r_node_num;
	if (start <= min_idx && end >= max_idx) {
		t[node_num - 1].area = ((unsigned long long)(disc[max_idx] - disc[min_idx])) * (t[node_num - 1].H = H), t[node_num - 1].pd = 1;
		return;
	}
	push_down(node_num, min_idx, max_idx);
	mid_idx = (min_idx + max_idx) >> 1, l_node_num = node_num << 1, r_node_num = l_node_num | 1;
	if (start < mid_idx) update(l_node_num, min_idx, mid_idx, start, end, H);
	if (end > mid_idx) update(r_node_num, mid_idx, max_idx, start, end, H);
	t[node_num - 1].area = t[l_node_num - 1].area + t[r_node_num - 1].area;
}

int main(int argc, char *argv[]) {
	unsigned int n, prev;
	scanf("%u", &N);
	for (n = 0; n < N; ++n) scanf("%u%u%u", &b[n].A, &b[n].B, &b[n].H), disc[n << 1] = b[n].A, disc[(n << 1) + 1] = b[n].B;
	qsort(disc, N << 1, sizeof(unsigned int), cmp);
	for (prev = disc[0], n = 1, cnt = 1; n < (N << 1); ++n) if (disc[n] != prev) prev = disc[cnt++] = disc[n];
	qsort(b, N, sizeof(struct bldg), cmp_by_h);
	init(1, 0, cnt - 1);
	for (n = 0; n < N; ++n) update(1, 0, cnt - 1, find_idx(b[n].A), find_idx(b[n].B), b[n].H);
	printf("%llu\n", t[0].area);
	return 0;
}
