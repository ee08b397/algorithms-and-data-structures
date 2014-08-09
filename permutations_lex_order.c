#include <stdio.h>

#define MAX_N 8

int main(int argc, char *argv[]) {
	unsigned int N, n, a, b, s, t, tmp, P[MAX_N];
	while (scanf("%u", &N), N) {
		for (n = 0; n < N; ++n) P[n] = n;
		while (1) {
			for (n = 0; n < N; ++n) printf("%u%c", P[n], n + 1 == N ? '\n' : ' ');
			for (s = N - 1; s && P[s - 1] > P[s]; --s);
			if (!s) break;
			for (t = N - 1; P[t] < P[s - 1]; --t);
			tmp = P[t], P[t] = P[s - 1], P[s - 1] = tmp;
			for (a = s, b = N - 1; a < b; ++a, --b) tmp = P[a], P[a] = P[b], P[b] = tmp;
		}
	}
	return 0;
}
