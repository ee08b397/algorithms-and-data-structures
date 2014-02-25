#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 128
#define MAX_LEN 100012
#define MAX_LG 17
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

size_t suffix_array[MAX_LEN], sa_inverse[MAX_LEN], cumulative_count[MAX_LEN], primary_rank[MAX_LEN], inv_secondary_rank[MAX_LEN], h[MAX_LEN], min_h[MAX_LG][MAX_LEN], l[MAX_LEN];

unsigned int msb(unsigned int x) {
	static const unsigned int bval[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
	unsigned int r = 0;
	if (x & 0xFFFF0000) { r += 16; x >>= 16; }
	if (x & 0x0000FF00) { r += 8; x >>= 8; }
	if (x & 0x000000F0) { r += 4; x >>= 4; }
	return r + bval[x];
}

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
	/*
	for (r = 0; r < length; ++r) printf("%lu %c\n", r, str[suffix_array[r]]);
	*/
	for (w = 1, p = 1; p < length; w <<= 1, num_elem = p) {
		/* first sort lexicographically by second half of each substring (storing their beginning positions in that order) */
		for (r = 0, s = length - w; s < length; ++s) inv_secondary_rank[r++] = s;  /* all substrings with empty second halves */ 

		for (rr = 0; rr < length; ++rr) if (suffix_array[rr] >= w) inv_secondary_rank[r++] = suffix_array[rr] - w;  /* all substrings with non-empty second halves (arranged by lex order of the second halves) */
		/* for (r = 0; r < length; ++r) tmp[r] = primary_rank[inv_secondary_rank[r]];  // lex ranks of the corresponding first halves */
		for (m = 0; m < num_elem; ++m) cumulative_count[m] = 0;	
		/* sort lexicographically by first half or each substring */
		for (r = 0; r < length; ++r) ++cumulative_count[primary_rank[inv_secondary_rank[r]]]; 
		for (m = 1; m < num_elem; ++m) cumulative_count[m] += cumulative_count[m - 1];
		for (r = length; r; --r) suffix_array[--cumulative_count[primary_rank[inv_secondary_rank[r - 1]]]] = inv_secondary_rank[r - 1];  /* sort by first halves */
		/*
		for (r = 0; r < length; ++r) {
			printf("%lu ", r); 
			for (size_t pos = suffix_array[r]; pos <= suffix_array[r] + w && pos < length; ++pos) {
				printf("%c", str[pos]);
			}
			printf("\n");
		}
		*/
		temp_ptr = inv_secondary_rank; inv_secondary_rank = primary_rank; primary_rank = temp_ptr;
		primary_rank[suffix_array[0]] = 0;
		for (r = 1, p = 1; r < length; ++r) primary_rank[suffix_array[r]] = (inv_secondary_rank[suffix_array[r - 1]] == inv_secondary_rank[suffix_array[r]] && inv_secondary_rank[suffix_array[r - 1] + w] == inv_secondary_rank[suffix_array[r] + w] ? p - 1 : p++);  
	}
}

size_t compute_lcp(const size_t a, const size_t b, const size_t sa_inverse[], const size_t min_h[][MAX_LEN]) {
	unsigned int p;
	size_t A = sa_inverse[a], B = sa_inverse[b], tmp;
	if (B == A) return 0;
	if (B < A) { tmp = A; A = B; B = tmp; }
	p = msb(B - A);
	return MIN(min_h[p - 1][A], min_h[p - 1][B - (1 << (p - 1))]);
}

int main(int argc, char *argv[]) {
	unsigned int case_num = 0;
	char str[MAX_LEN + 1];
	size_t length, r, j, k, L, p, w, a, b, lcp, s, ts, tl, max, num; 
	while (scanf("%s", str) != EOF && str[0] != '#') {
		max = 0;
		num = 0;
		compute_suffix_array(length = strlen(str), str, suffix_array, cumulative_count, primary_rank, inv_secondary_rank);
		for (k = 0; k < length; ++k) sa_inverse[suffix_array[k]] = k;
		for (k = 0; k + 1 < length; ++k) {
			for (a = suffix_array[k], b = suffix_array[k + 1], h[k] = 0; str[a] && str[b] && str[a] == str[b]; ++a, ++b, ++h[k]);
			min_h[0][k] = h[k];
		}
		for (p = 1, w = 1; p <= MAX_LG; ++p, w <<= 1) for (k = 0; k + 1 < length; ++k) min_h[p][k] = MIN(min_h[p - 1][k], k + w + 1 < length ? min_h[p - 1][k + w] : 0);
		for (L = 1; L < length; ++L) {
			for (k = 0; k + L < length; k += L) {	
				lcp = compute_lcp(k, k + L, sa_inverse, (const size_t (*)[MAX_LEN])min_h);
				s = lcp / L + 1;
				if (k >= L - lcp % L && lcp % L && compute_lcp(k - (L - lcp % L), k - (L - lcp % L) + L, sa_inverse, (const size_t (*)[MAX_LEN])min_h) >= lcp) ++s;   /* prefix */
				if (s > max) {
					num = 0;
					l[num++] = L;
					max = s;
				}else if (s == max) {
					l[num++] = L;
				}
			}
		}
		L = 0;
		tl = 0;
		for (r = 0; r <= length; ++r) {
			ts = suffix_array[r]; 
			for (j = 0; j < num; ++j) {
				tl = l[j];
				if (compute_lcp(ts, ts + tl, sa_inverse, (const size_t (*)[MAX_LEN])min_h) >= (max - 1) * tl) { 
					L = tl * max;
					printf("Case %u: ", ++case_num);
					for (k = 0; k < L; ++k) printf("%c", str[ts + k]); 
					printf("\n");
					r = length;
					break;
				}
			}
		}
	}
	return 0;
}
