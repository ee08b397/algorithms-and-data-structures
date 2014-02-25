#include <stdio.h>

#define MAX_N 250000
#define MAX_H 9999
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void scc(const unsigned int W, const unsigned int L, const unsigned int n, const unsigned int H[], unsigned int ll[], unsigned int *const current_index, unsigned int index[], unsigned int *const s_size, unsigned int s[], unsigned int in_s[], unsigned int *const num_scc, unsigned int *const num_zero_in_deg, unsigned int *const num_zero_out_deg) {
	const unsigned int l = n / W, w = n % W;
	unsigned int c, current_l, current_w, has_in_deg = 0, has_out_deg = 0;
	ll[n] = index[n] = (*current_index)++;
	s[(*s_size)++] = n;
	in_s[n] = 1;
	if (l && H[n - W] <= H[n]) { if (index[n - W] == MAX_N + 1) scc(W, L, n - W, H, ll, current_index, index, s_size, s, in_s, num_scc, num_zero_in_deg, num_zero_out_deg), ll[n] = MIN(ll[n], ll[n - W]); else if (in_s[n - W]) ll[n] = MIN(ll[n], index[n - W]); }
	if (l + 1 < L && H[n + W] <= H[n]) { if (index[n + W] == MAX_N + 1) scc(W, L, n + W, H, ll, current_index, index, s_size, s, in_s, num_scc, num_zero_in_deg, num_zero_out_deg), ll[n] = MIN(ll[n], ll[n + W]); else if (in_s[n + W]) ll[n] = MIN(ll[n], index[n + W]); }
	if (w && H[n - 1] <= H[n]) { if (index[n - 1] == MAX_N + 1) scc(W, L, n - 1, H, ll, current_index, index, s_size, s, in_s, num_scc, num_zero_in_deg, num_zero_out_deg), ll[n] = MIN(ll[n], ll[n - 1]); else if (in_s[n - 1]) ll[n] = MIN(ll[n], index[n - 1]); }
	if (w + 1 < W && H[n + 1] <= H[n]) { if (index[n + 1] == MAX_N + 1) scc(W, L, n + 1, H, ll, current_index, index, s_size, s, in_s, num_scc, num_zero_in_deg, num_zero_out_deg), ll[n] = MIN(ll[n], ll[n + 1]); else if (in_s[n + 1]) ll[n] = MIN(ll[n], index[n + 1]); }
	if (ll[n] == index[n]) {
		while (1) {
			c = s[--(*s_size)];
			in_s[c] = 0;
			if (!has_in_deg || !has_out_deg) {
				current_l = c / W, current_w = c % W;
				if (current_l) { if (H[c - W] < H[c]) has_out_deg = 1; else if (H[c - W] > H[c]) has_in_deg = 1; }
				if (has_in_deg && has_out_deg) { if (c == n) break; else continue; }
				if (current_l + 1 < L) { if (H[c + W] < H[c]) has_out_deg = 1; else if (H[c + W] > H[c]) has_in_deg = 1; }
				if (has_in_deg && has_out_deg) { if (c == n) break; else continue; }
				if (current_w) { if (H[c - 1] < H[c]) has_out_deg = 1; else if (H[c - 1] > H[c]) has_in_deg = 1; }
				if (has_in_deg && has_out_deg) { if (c == n) break; else continue; }
				if (current_w + 1 < W) { if (H[c + 1] < H[c]) has_out_deg = 1; else if (H[c + 1] > H[c]) has_in_deg = 1; }
			}
			if (c == n) break;
		}
		++(*num_scc);
		if (!has_in_deg) ++(*num_zero_in_deg);
		if (!has_out_deg) ++(*num_zero_out_deg);
	}
}

int main(int argc, char *argv[]) {
	unsigned int W, L, N, n, s_size, current_index, num_scc, num_zero_in_deg, num_zero_out_deg, max_H = 0, min_H = MAX_H;
	unsigned int index[MAX_N], ll[MAX_N], H[MAX_N], s[MAX_N], in_s[MAX_N];
	scanf("%u%u", &W, &L);
	N = W * L;
	for (n = 0; n < N; ++n) {
		scanf("%u", &H[n]);
		in_s[n] = 0;
		index[n] = MAX_N + 1;
		if (H[n] > max_H) max_H = H[n];
		if (H[n] < min_H) min_H = H[n];
	}
	if (max_H == min_H) {  /* note: one needs to bypass this case, otherwise a stackoverflow occurs */
		printf("0\n");
		return 0;
	}
	current_index = 0, s_size = 0, num_scc = 0, num_zero_in_deg = 0, num_zero_out_deg = 0;
	for (n = 0; n < N; ++n) if (index[n] == MAX_N + 1) scc(W, L, n, H, ll, &current_index, index, &s_size, s, in_s, &num_scc, &num_zero_in_deg, &num_zero_out_deg);
	printf("%u\n", num_scc <= 1 ? 0 : MAX(num_zero_in_deg, num_zero_out_deg));
	return 0;
}
