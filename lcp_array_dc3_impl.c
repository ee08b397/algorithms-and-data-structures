/* source code from the original DC3 paper, plus some minor improvements */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEN 100005

unsigned char str[MAX_LEN + 1];
size_t cnt[MAX_LEN + 3], s[MAX_LEN + 3], sa[MAX_LEN + 3], r[MAX_LEN], h[MAX_LEN];

inline int leq2(const size_t a1, const size_t a2, const size_t b1, const size_t b2) { /* (a1, a2) <= (b1, b2) */
	return (a1 < b1 || (a1 == b1 && a2 <= b2)); 
}

inline int leq3(const size_t a1, const size_t a2, const size_t a3, const size_t b1, const size_t b2, const size_t b3) {
	return (a1 < b1 || (a1 == b1 && leq2(a2, a3, b2, b3)));
}

static void radix_pass(const size_t *const src, size_t *const dest, const size_t *const s, const size_t length, const size_t num_grp) {
	size_t i, sum, t;
	for (i = 0; i <= num_grp; ++i) cnt[i] = 0;
	for (i = 0; i < length; ++i) ++cnt[s[src[i]]];
	for (i = 0, sum = 0; i <= num_grp; ++i) { t = cnt[i]; cnt[i] = sum; sum += t; }
	for (i = 0; i < length; ++i) dest[cnt[s[src[i]]]++] = src[i];
}

void compute_suffix_array(const size_t *const s, size_t *const suffix_array, const size_t length, const unsigned int max_val) {
	const size_t L0 = (length + 2) / 3, L1 = (length + 1) / 3, L2 = length / 3, L02 = L0 + L2;
	size_t i, j, label, p, t, k, c0, c1, c2, *const s12 = (size_t *)malloc((L02 + 3) * sizeof(size_t)), *const suffix_array12 = (size_t *)malloc((L02 + 3) * sizeof(size_t)), *const s0 = (size_t *)malloc(L0 * sizeof(size_t)), *const suffix_array0 = (size_t *)malloc(L0 * sizeof(size_t));
	s12[L02] = s12[L02 + 1] = s12[L02 + 2] = 0;  /* pading with 0s */
	suffix_array12[L02] = suffix_array12[L02 + 1] = suffix_array12[L02 + 2] = 0;
	for (i = 0, j = 0; i < length + L0 - L1; ++i) if (i % 3) s12[j++] = i;
	radix_pass(s12, suffix_array12, s + 2, L02, max_val);
	radix_pass(suffix_array12, s12, s + 1, L02, max_val);
	radix_pass(s12, suffix_array12, s, L02, max_val);
	label = 0, c0 = c1 = c2 = UINT_MAX;
	for (i = 0; i < L02; ++i) {
		if (s[suffix_array12[i]] != c0 || s[suffix_array12[i] + 1] != c1 || s[suffix_array12[i] + 2] != c2) {
			++label;
			c0 = s[suffix_array12[i]];
			c1 = s[suffix_array12[i] + 1];
			c2 = s[suffix_array12[i] + 2];
		}
		if (1 == suffix_array12[i] % 3) s12[suffix_array12[i] / 3] = label; else s12[suffix_array12[i] / 3 + L0] = label;
	}
	if (label < L02) {
		compute_suffix_array(s12, suffix_array12, L02, label);
		for (i = 0; i < L02; ++i) s12[suffix_array12[i]] = i + 1;
	} else
		for (i = 0; i < L02; ++i) suffix_array12[s12[i] - 1] = i;
	for (i = 0, j = 0; i < L02; ++i) if (suffix_array12[i] < L0) s0[j++] = 3 * suffix_array12[i];
	radix_pass(s0, suffix_array0, s, L0, max_val);
	for (p = 0, t = L0 - L1, k = 0; k < length; ++k) {
		i = (suffix_array12[t] < L0 ? suffix_array12[t] * 3 + 1 : (suffix_array12[t] - L0) * 3 + 2);
		j = suffix_array0[p];
		if (suffix_array12[t] < L0 ? leq2(s[i], s12[suffix_array12[t] + L0], s[j], s12[j / 3]) : leq3(s[i], s[i + 1], s12[suffix_array12[t] - L0 + 1], s[j], s[j + 1], s12[j / 3 + L0])) {
			suffix_array[k] = i; ++t;
			if(t == L02) for (++k; p < L0; ++p, ++k) suffix_array[k] = suffix_array0[p];
		} else {
			suffix_array[k] = j; ++p;
			if (p == L0) for (++k; t < L02; ++t, ++k) suffix_array[k] = (suffix_array12[t] < L0 ? suffix_array12[t] * 3 + 1 : (suffix_array12[t] - L0) * 3 + 2);
		}
	}
	free(s12), free(suffix_array12), free(suffix_array0), free(s0);
}

void compute_lcp_array(const size_t length, const size_t *const suffix_array, size_t *const rank, size_t *const lcp_array) {
	size_t i, j, h;
	for (i = 0; i < length; ++i) rank[suffix_array[i]] = i;
	for (h = 0, i = 1; i < length; ++i) {
		if (rank[i]) {
			for (j = suffix_array[rank[i] - 1]; str[i + h] && str[j + h] && str[i + h] == str[j + h]; ++h);
			lcp_array[rank[i]] = h;
			if (h) --h;
		}
	}
}

int main(int argc, char *argv[]) {
	unsigned int max_val;
	size_t n, len;
	while (EOF != scanf("%s", str)) {
		for (max_val = 0, n = 0; str[n]; ++n) { s[n] = str[n]; if (str[n] > max_val) max_val = str[n]; }
		len = n + 1;
		for (n = len; n < len + 3; ++n) sa[n] = s[n] = 0;
		compute_suffix_array(s, sa, len, max_val);
		for (n = 0; n < len; ++n) printf("%lu ", sa[n]);
		printf("\n");
		compute_lcp_array(len, sa, r, h);
		for (n = 0; n < len; ++n) printf("%lu ", h[n]); 
		printf("\n");
	}
	return 0;
}
