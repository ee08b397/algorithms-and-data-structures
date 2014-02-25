#include <stdio.h>

#define MAX_L 20

int main(int argc, char *argv[]) {
	char w[MAX_L + 1];
	unsigned int i, prev_snd, s, snd[26] = {0, 1, 2, 3, 0, 1, 2, 0, 0, 2, 2, 4, 5, 5, 0, 1, 2, 6, 2, 3, 0, 1, 0, 2, 0, 2};
	while (scanf("%s", w) != EOF) {
		for (prev_snd = 0, i = 0; w[i]; ++i) if ((s = snd[w[i] - 'A']) != prev_snd) if ((prev_snd = s)) putc('0' + s, stdout);
		putc('\n', stdout);
	}
	return 0;
}
