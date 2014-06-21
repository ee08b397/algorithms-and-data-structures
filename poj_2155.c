#include <stdio.h>

#define MAX_INS_LEN 2
#define MAX_NUM_BYTE 125
#define CHANGE 'C'

unsigned int N;
unsigned char data[MAX_NUM_BYTE << 3][MAX_NUM_BYTE];

void change(const unsigned int X, const unsigned int Y) {
	unsigned int x, y;
	for (y = Y; y <= N; y += y & -y) for (x = X; x <= N; x += x & -x) data[y - 1][(x - 1) >> 3] ^= (1 << ((x - 1) & 0x07));
}

unsigned int query(const unsigned int X, const unsigned int Y) {
	unsigned int x, y, result; 
	for (result = 0, y = Y; y; y -= y & -y) for (x = X; x; x -= x & -x) result ^= (data[y - 1][(x - 1) >> 3] >> ((x - 1) & 0x07)) & 0x01;
	return result;
}

int main(int argc, char *argv[]) {
	char ins[MAX_INS_LEN + 1];
	unsigned int T, num_ins, num_byte, i, j, x1, y1, x2, y2;
	scanf("%u", &T);
	while (T--) {
		scanf("%u%u", &N, &num_ins), num_byte = (N + 8 - (N & 0x07)) >> 3;
		for (i = 0; i < N; ++i) for (j = 0; j < num_byte; ++j) data[i][j] = 0;
		while (num_ins--) {
			scanf("%s", ins);
			if (CHANGE == ins[0]) scanf("%u%u%u%u", &x1, &y1, &x2, &y2), change(x1, y1), change(x2 + 1, y1), change(x1, y2 + 1), change(x2 + 1, y2 + 1); else scanf("%u%u", &x1, &y1), printf("%u\n", query(x1, y1));
		}
		if (T) printf("\n");
	}
	return 0;
}
