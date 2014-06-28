#include <stdio.h>
#include <assert.h>

#define MAX_N 500000
#define MAX_T 524288
#define MAX_LEN 10
#define NUM_ANTI_PRIME 37

char name[MAX_N][MAX_LEN + 1];
int N, K, M, P, num[MAX_N], anti_prime[NUM_ANTI_PRIME] = {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, 45360, 50400, 55440, 83160, 110880, 166320, 221760, 277200, 332640, 498960, 500001}, f[NUM_ANTI_PRIME] = {1, 2, 3, 4, 6, 8, 9, 10, 12, 16, 18, 20, 24, 30, 32, 36, 40, 48, 60, 64, 72, 80, 84, 90, 96, 100, 108, 120, 128, 144, 160, 168, 180, 192, 200, 1314521}, t[MAX_T << 1];

int modulo(const int a, const int b) {
	int r;
	return (r = (a % b)) < 0 ? r + b : r;
}

int find_p(const int x) {
	int min, max, mid;  
	for (min = 0, max = NUM_ANTI_PRIME - 1; max > min;) if (anti_prime[mid = (max + min) >> 1] <= x) min = mid + 1; else max = mid;
	return max - 1;
}

void init(const int node_num, const int min, const int max) {
	int mid;
	t[node_num] = max - min + 1;
	if (min == max) return;
	mid = (min + max) >> 1, init(node_num << 1, min, mid), init((node_num << 1) | 1, mid + 1, max);
}

int jmp(const int k, const int node_num, const int min, const int max) {
	int mid;
	--t[node_num];
	if (min == max) return min;
	mid = (min + max) >> 1;
	return k <= t[node_num << 1] ? jmp(k, node_num << 1, min, mid) : jmp(k - t[node_num << 1], (node_num << 1) | 1, mid + 1, max);
}

int main(int argc, char *argv[]) {
	int n, k, i, offset;
	while (EOF != scanf("%u%u", &N, &K)) {
		i = find_p(N), M = f[i], P = anti_prime[i]; 
		init(1, 1, N);
		for (n = 0; n < N; ++n) scanf("%s%d", name[n], &num[n]);
		for (n = 0, k = K, offset = 0; n < P; ++n) offset = num[i = jmp(k = modulo(offset > 0 ? k - 2 + offset : k - 1 + offset, t[1]) + 1, 1, 1, N) - 1];
		printf("%s %d\n", name[i], M);
	}
	return 0;
}
