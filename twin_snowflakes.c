#include <stdio.h>

#define NUM 6
#define HT_SIZE 391939
#define MAX_N 100000

struct ent {
	unsigned int idx;
	struct ent *next;
};

int is_sim(const unsigned int idx1, const unsigned int idx2, const unsigned int l[][6]) {
	unsigned int i, j, sim;
	for (j = 0; j < 6; ++j) {
		sim = 1;
		for (i = 0; i < 6; ++i) {
			if (l[idx1][i] != l[idx2][(i + j) % 6]) {
				sim = 0;
				break;
			}
		}
		if (sim) {
			return 1;
		}
		sim = 1;
		for (i = 0; i < 6; ++i) {
			if (l[idx1][5 - i] != l[idx2][(i + j) % 6]) {
				sim = 0;
				break;
			}
		}
		if (sim) {
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	unsigned int h, hvalue, n, N, l[MAX_N][6];
	struct ent e[MAX_N], *ht[HT_SIZE], *ptr;
	for (h = 0; h < HT_SIZE; ++h) {
		ht[h] = NULL;
	}
	scanf("%u", &N);
	for (n = 0; n < N; ++n) {
		scanf("%u %u %u %u %u %u", &l[n][0], &l[n][1], &l[n][2], &l[n][3], &l[n][4], &l[n][5]);
		hvalue = 0;
		for (h = 0; h < 6; ++h) {
			hvalue += l[n][h] % HT_SIZE;
			/*
			hvalue %= HT_SIZE;
			*/
		}
		hvalue %= HT_SIZE;
		e[n].idx = n;
		e[n].next = ht[hvalue];
		ptr = ht[hvalue];
		while (ptr) {	
			if (is_sim(ptr -> idx, n, (const unsigned int(*)[6])l)) {
				printf("Twin snowflakes found.\n");
				return 0;
			}
			ptr = ptr -> next;
		}
		ht[hvalue] = &e[n];
	}
	printf("No two snowflakes are alike.\n");
	return 0;
}
