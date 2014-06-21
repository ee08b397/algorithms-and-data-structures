#include <stdio.h>

#define MAX_N 250
#define MAX_L 8  /* 2^0, .., 2^7 */

unsigned short N, B, min[MAX_N][MAX_N][MAX_L], max[MAX_N][MAX_N][MAX_L];
unsigned int K;

int main(int argc, char *argv[]) {
	unsigned short i, j, ri, rj, l, w, h, current_max, current_min;
	scanf("%hu%hu%u", &N, &B, &K);
	for (i = 0; i < N; ++i) for (j = 0; j < N; ++j) scanf("%hu", &h), max[i][j][0] = min[i][j][0] = h;
	w = 1, l = 0;
	while ((w << 1) < B) {
		++l;
		for (i = 0, ri = w; i < N; ++i, ++ri)
			for (j = 0, rj = w; j < N; ++j, ++rj) {
				max[i][j][l] = max[i][j][l - 1];
				if (ri < N && max[ri][j][l - 1] > max[i][j][l]) max[i][j][l] = max[ri][j][l - 1];
				if (rj < N && max[i][rj][l - 1] > max[i][j][l]) max[i][j][l] = max[i][rj][l - 1];
				if (ri < N && rj < N && max[ri][rj][l - 1] > max[i][j][l]) max[i][j][l] = max[ri][rj][l - 1];
				min[i][j][l] = min[i][j][l - 1];
				if (ri < N && min[ri][j][l - 1] < min[i][j][l]) min[i][j][l] = min[ri][j][l - 1];
				if (rj < N && min[i][rj][l - 1] < min[i][j][l]) min[i][j][l] = min[i][rj][l - 1];
				if (ri < N && rj < N && min[ri][rj][l - 1] < min[i][j][l]) min[i][j][l] = min[ri][rj][l - 1];
			}
		w <<= 1;
	}
	while (K--) {
		scanf("%hu%hu", &i, &j), --i, --j, ri = i + B - w, rj = j + B - w;
		current_max = max[i][j][l];
		if (ri < N && max[ri][j][l] > current_max) current_max = max[ri][j][l];
		if (rj < N && max[i][rj][l] > current_max) current_max = max[i][rj][l];
		if (ri < N && rj < N && max[ri][rj][l] > current_max) current_max = max[ri][rj][l];
		current_min = min[i][j][l];
		if (ri < N && min[ri][j][l] < current_min) current_min = min[ri][j][l];
		if (rj < N && min[i][rj][l] < current_min) current_min = min[i][rj][l];
		if (ri < N && rj < N && min[ri][rj][l] < current_min) current_min = min[ri][rj][l];
		printf("%u\n", current_max - current_min); 
	}
	return 0;
}
