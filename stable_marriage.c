/*
 *   POJ 3487: The Stable Marriage Problem
 *
 *   Memory: 160K    Time: 0MS    Language: C    Submit Time: 2014-04-13 04:23:29
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_L 2 
#define MAX_N 26
#define MAX_QL 1024

int cmp(const void *const a, const void *const b) {
	return *((const char *const)a) < *((const char *const)b) ? -1 : 1;
}

int main(int argc, char *argv[]) {
	char c[MAX_L + 1], sorted_m_list[MAX_N], m_list[MAX_N], f_list[MAX_N], pref_str[MAX_N + 4];
	unsigned int T, N, n, p, cnd, w, m, __m, q_front, q_back, q[MAX_QL], m_map[MAX_N], f_map[MAX_N], m_nxt[MAX_N], m_cnd[MAX_N], f_cnd[MAX_N], m_pref[MAX_N][MAX_N], f_pref[MAX_N][MAX_N];
	scanf("%u", &T);
	while (T--) {
		scanf("%u", &N);
		for (n = 0; n < N; ++n) m_nxt[n] = 0, f_cnd[n] = MAX_N + 1, q[n] = n;
		q_front = 0, q_back = N;
		for (n = 0; n < N; ++n) scanf("%s", c), sorted_m_list[n] = m_list[n] = c[0], m_map[c[0] - 'a'] = n;
		qsort(sorted_m_list, N, sizeof(char), cmp);
		for (n = 0; n < N; ++n) scanf("%s", c), f_list[n] = c[0], f_map[c[0] - 'A'] = n;
		for (n = 0; n < N; ++n) { scanf("%s", pref_str); for (cnd = pref_str[0] - 'a', p = 0; p < N; ++p) m_pref[cnd][p] = f_map[pref_str[p + 2] - 'A']; }
		for (n = 0; n < N; ++n) { scanf("%s", pref_str); for (cnd = pref_str[0] - 'A', p = 0; p < N; ++p) f_pref[cnd][m_map[pref_str[p + 2] - 'a']] = p; }
		while (q_back > q_front) { m = q[q_front++], w = m_pref[m][m_nxt[m]]; if (MAX_N + 1 == f_cnd[w]) f_cnd[w] = m, m_cnd[m] = w; else if (f_pref[w][__m = f_cnd[w]] > f_pref[w][m]) q[q_back++] = __m, ++m_nxt[__m], f_cnd[w] = m, m_cnd[m] = w; else q[q_back++] = m, ++m_nxt[m]; }
		for (n = 0; n < N; ++n) putc(sorted_m_list[n], stdout), putc(' ', stdout), putc(f_list[m_cnd[m_map[sorted_m_list[n] - 'a']]], stdout), putc('\n', stdout);
		if (T) putc('\n', stdout);
	}
	return 0;
}
