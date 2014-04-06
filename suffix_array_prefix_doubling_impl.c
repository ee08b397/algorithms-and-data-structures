#include <stdio.h>
#include <string.h>

#define MAX_LEN 100005
#define ALPHABET_SIZE 127

char str[MAX_LEN + 1];
size_t suffix_array[MAX_LEN], cumulative_count[ALPHABET_SIZE + 1], primary_rank[MAX_LEN], inv_secondary_rank[MAX_LEN];
/*
  suffix_array[r]: starting position of the r-th lexicographically smallest suffix
  inv_secondary_rank: starting position of substrings with the r-th lexicographically smallest second half (second half can be empty)
  primary_rank: lexicographical rank of each substring of length 2*w at end of iteration w
 */
void compute_suffix_array(const size_t length, const char str[], size_t suffix_array[], size_t cumulative_count[], size_t primary_rank[], size_t inv_secondary_rank[]) {
	const size_t M = ALPHABET_SIZE + 1;
	size_t num_elem = M, p, r, rr, m, s, w;
	size_t *temp_ptr; 
	for (m = 0; m < M; ++m) cumulative_count[m] = 0; 
	for (s = 0; s < length; ++s) ++cumulative_count[primary_rank[s] = str[s]];
	for (m = 1; m < M; ++m) cumulative_count[m] += cumulative_count[m - 1];
	for (s = length; s; --s) suffix_array[--cumulative_count[primary_rank[s - 1]]] = s - 1;
	for (w = 1, p = 1; p < length; w <<= 1, num_elem = p) {
		/* first sort lexicographically by second half of each substring (storing their beginning positions in that order) */
		for (r = 0, s = length - w; s < length; ++s) inv_secondary_rank[r++] = s;  /* all substrings with empty second halves */ 
		for (rr = 0; rr < length; ++rr) if (suffix_array[rr] >= w) inv_secondary_rank[r++] = suffix_array[rr] - w;  /* all substrings with non-empty second halves (arranged by lex order of the second halves) */
		for (m = 0; m < num_elem; ++m) cumulative_count[m] = 0;	
		/* sort lexicographically by first half or each substring */
		for (r = 0; r < length; ++r) ++cumulative_count[primary_rank[inv_secondary_rank[r]]]; 
		for (m = 1; m < num_elem; ++m) cumulative_count[m] += cumulative_count[m - 1];
		for (r = length; r; --r) suffix_array[--cumulative_count[primary_rank[inv_secondary_rank[r - 1]]]] = inv_secondary_rank[r - 1];  /* sort by first halves */
		temp_ptr = inv_secondary_rank; inv_secondary_rank = primary_rank; primary_rank = temp_ptr;
		primary_rank[suffix_array[0]] = 0;
		for (r = 1, p = 1; r < length; ++r) primary_rank[suffix_array[r]] = (inv_secondary_rank[suffix_array[r - 1]] == inv_secondary_rank[suffix_array[r]] && inv_secondary_rank[suffix_array[r - 1] + w] == inv_secondary_rank[suffix_array[r] + w] ? p - 1 : p++);  
	}
}

int main(int argc, char *argv[]) {
	size_t i, length;
	while (scanf("%s", str) != EOF) {
		scanf("%s", str);
		length = strlen(str);
		compute_suffix_array(length, str, suffix_array, cumulative_count, primary_rank, inv_secondary_rank);
		for (i = 0; i < length; ++i) printf("%lu ", suffix_array[i]);
		printf("\n");
	}
	return 0;
}
