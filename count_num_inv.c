#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50
#define MAX_NUM_STR 100

struct dna {
	size_t idx;
	size_t num_inv;
	char str[MAX_LEN + 1];
};

int comp(const void *p1, const void *p2) {
	return ((*(struct dna **)p1) -> num_inv < (*(struct dna **)p2) -> num_inv || ((*(struct dna **)p1) -> num_inv == (*(struct dna **)p2) -> num_inv && (*(struct dna **)p1) -> idx < (*(struct dna **)p2) -> idx)) ? -1 : 1;
}

size_t count_num_inv(const size_t start, const size_t end, char str[], char tmp[]) {
	if (start == end) {
		return 0;
	}
	size_t idx, l_idx, r_idx, num_inv;
	size_t mid = (start + end) >> 1;
	num_inv = count_num_inv(start, mid, str, tmp) + count_num_inv(mid + 1, end, str, tmp);	
	for (idx = start; idx <= end; ++idx) {
		tmp[idx] = str[idx];
	}
	idx = start;
	l_idx = start;
	r_idx = mid + 1;
	while (l_idx <= mid && r_idx <= end) {
		if (tmp[r_idx] < tmp[l_idx]) {
			str[idx++] = tmp[r_idx++];
			num_inv += mid + 1 - l_idx;
		}else {
			str[idx++] = tmp[l_idx++];
		}
	}
	while (l_idx <= mid) {
		str[idx++] = tmp[l_idx++];
	}
	while (r_idx <= end) {
		str[idx++] = tmp[r_idx++];
	}
	return num_inv;
}

int main(int argc, char *argv[]) {
	unsigned int n, N;
	size_t length;
	char str[MAX_LEN + 1], tmp[MAX_LEN + 1];
	struct dna dna_ent[MAX_NUM_STR], *dna_ptr[MAX_NUM_STR];
	/*

	some test data for counting # of inversion(s) 

	strcpy(str, "ZWQM");
	printf("%lu\n", count_num_inv(0, 3, str, tmp));  
	printf("%s\n", str);
	strcpy(str, "AACEDGG");
	printf("%lu\n", count_num_inv(0, 6, str, tmp));  
	printf("%s\n", str);
	strcpy(str, "DAABEC");
	printf("%lu\n", count_num_inv(0, 5, str, tmp));  
	printf("%s\n", str);
	*/
	scanf("%lu", &length);
	scanf("%u", &N);
	for (n = 0; n < N; ++n) {
		dna_ent[n].idx = n;
		scanf("%s", str);
		strcpy(dna_ent[n].str, str);
		dna_ent[n].num_inv = count_num_inv(0, length - 1, str, tmp);
		dna_ptr[n] = &(dna_ent[n]);
	}
	qsort(dna_ptr, N, sizeof(struct dna *), comp);
	for (n = 0; n < N; ++n) {
		printf("%s\n", dna_ptr[n] -> str);
	}
	return 0;
}
