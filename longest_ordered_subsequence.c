#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

unsigned int __longest_ordered_seq(const unsigned int n, const unsigned int N, const unsigned int seq[], int len[]) {
	unsigned int k, result, max_result = 1;
	if (n == N) {
		return 0;
	}
	if (len[n] >= 0) {
		return len[n];
	}
	for (k = n + 1; k < N; ++k) { 
		if (seq[k] > seq[n]) {
			if ((result = 1 + __longest_ordered_seq(k, N, seq, len)) > max_result) {
				max_result = result;
			}
		}
	}
	len[n] = max_result;
	return max_result;
}

unsigned int longest_ordered_seq(const unsigned int N, const unsigned int seq[], int len[]) {
	unsigned int n, result, max_result = 0;
	for (n = 0; n < N; ++n) {
		if ((result = __longest_ordered_seq(n, N, seq, len)) > max_result) {
			max_result = result;
		}
	}
	return max_result;
}

int main(int argc, char *argv[]) {
	unsigned int n, N, seq[MAX_N];
	int len[MAX_N];
	scanf("%u", &N);
	for (n = 0; n < N; ++n) {
		scanf("%u", &seq[n]);
		len[n] = -1;
	}
	printf("%u\n", longest_ordered_seq(N, seq, len));
	return 0;
}
