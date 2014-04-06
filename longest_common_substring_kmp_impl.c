/*
 *   POJ 3450: Corporate Identity
 *
 *   Memory: 968K    Time: 94MS    Language: C    Submit Time: 2014-04-06 09:45:34
 *
 */

#include <stdio.h>
#include <string.h>

#define MAX_N 4000
#define MAX_LEN 200

void build_kmp_table(int T[], const char *const W, const unsigned int wLen) {
	unsigned int pos, cnd;
	for (T[0] = -1, T[1] = 0, pos = 2, cnd = 0; pos < wLen;) if (W[pos - 1] == W[cnd]) T[pos++] = ++cnd; else if (cnd) cnd = T[cnd]; else T[pos++] = 0; 
}

unsigned int kmp_match(const char *const W, const char *const S, const unsigned int wLen, const unsigned int sLen, const int T[]) {
	unsigned int m, i;
	for (m = 0, i = 0; m + i < sLen;) if (W[i] == S[m + i]) { if (i + 1 == wLen) return 1; ++i; } else m += i - T[i], i = (T[i] > -1 ? T[i] : 0); 
	return 0;
}

int main(int argc, char *argv[]) {
	unsigned int N, n, lost, min_len, min_len_idx, min_id_len, max_id_len, has_id, not_id, id_offset, id_len, L, idx, len[MAX_N];
	char str[MAX_N][MAX_LEN + 1];
	const char *id;
	int T[MAX_LEN];   /* KMP table */
	while (1) {
		scanf("%u", &N);
		if (!N) return 0;
		min_len = MAX_LEN + 1;
		min_len_idx = 0;
		for (n = 0; n < N; ++n) { scanf("%s", str[n]); if ((len[n] = strlen(str[n])) < min_len) min_len = len[n], min_len_idx = n; }
		min_id_len = 1, max_id_len = min_len, lost = 1, id_len = 0, id = NULL;
		while (min_id_len <= max_id_len) {   /* binary search on length of the identity */
			has_id = 0, L = (min_id_len + max_id_len) >> 1;
			for (id_offset = 0; id_offset + L <= min_len; ++id_offset) {
				if (L == id_len && strncmp(str[min_len_idx] + id_offset, id, L) >= 0) continue; /* since if there were multiple common substrings of the same length, only the lexicographically smallest one would be considered */
				build_kmp_table(T, str[min_len_idx] + id_offset, L);
				for (not_id = 0, idx = 0; idx < N; ++idx) {
					if (idx == min_len_idx) continue;
					if (!kmp_match(str[min_len_idx] + id_offset, str[idx], L, len[idx], T)) { not_id = 1; break; } 
				}
				if (!not_id) {
					has_id = 1;
					if (L >= id_len) id = str[min_len_idx] + id_offset, id_len = L, lost = 0;  
				}
			}
			if (has_id) min_id_len = L + 1; else max_id_len = L - 1; 
		}
		if (lost) printf("IDENTITY LOST\n"); else printf("%.*s\n", id_len, id);
	}
	return 0;
}
