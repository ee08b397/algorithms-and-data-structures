#include <stdio.h>

#define MAX_N 100000
#define MAX_L 17 
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

unsigned int msb(unsigned int x) {
	static const unsigned int bval[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
	unsigned int r = 0;
	if (x & 0xFFFF0000) { r += 16; x >>= 16; }
	if (x & 0x0000FF00) { r += 8; x >>= 8; }
	if (x & 0x000000F0) { r += 4; x >>= 4; }
	return r + bval[x];
}

int main(int argc, char *argv[]) {
	int c, c_v; 
	unsigned int n, q, k, p, w, num_v, lg_v, v_idx, a, b, v_a, v_b, f, max, v_map[MAX_N], v[MAX_N][2], max_freq[MAX_L][MAX_N];
	while (1) {
		scanf("%u", &n);
		if (!n) return 0;
		scanf("%u", &q);
		scanf("%d", &c_v);
		v_idx = 0;
		v[0][0] = 0;
		v_map[0] = 0;
		for (k = 1; k < n; ++k) {
			scanf("%d", &c);
			if (c != c_v) {
				v[v_idx][1] = k - 1;
				max_freq[0][v_idx] = k - v[v_idx][0];
				v[++v_idx][0] = k;
				c_v = c;
			}
			v_map[k] = v_idx;
		}
		v[v_idx][1] = n - 1;
		max_freq[0][v_idx] = n - v[v_idx][0];
		num_v = ++v_idx;
		/*
		for (k = 0; k < n; ++k) printf("%u ", v_map[k]);
		printf("\n");
		for (k = 0; k < num_v; ++k) printf(" [%u, %u] ", v[k][0], v[k][1]);
		printf("\n");
		*/
		/*
		printf("num_v == %u\n", num_v);
		for (k = 0; k < num_v; ++k) printf("%u ", max_freq[0][k]);
		printf("\n");
		*/
		lg_v = msb(num_v);
		/*
		printf("num_v == %u, lg_v == %u\n", num_v, lg_v); 
		*/
		for (p = 1, w = 1; p < lg_v; ++p, w <<= 1) {
			for (k = 0; k < num_v; ++k) {
				max_freq[p][k] = MAX(max_freq[p - 1][k], k + w < num_v ? max_freq[p - 1][k + w] : 0);
			}
		}
		while (q--) {
			scanf("%u%u", &a, &b);
			--a; --b;
			v_a = v_map[a];
			max = MIN(b, v[v_a][1]) + 1 - a; 
/* printf("v_a == %u, v[v_a][1] == %u, first freq == %u\n", v_a, v[v_a][1], max); */
			v_b = v_map[b];
/* printf("v_b == %u, v[v_b][0] == %u, last freq == %u\n", v_b, v[v_b][0], b + 1 - MAX(a, v[v_b][0])); */
			if ((f = b + 1 - MAX(a, v[v_b][0])) > max) max = f;
			if (v_a + 2 <= v_b) {/* v_a + 1 <= v_b - 1 */  
				w = v_b - v_a - 1;   /* (v_b - 1) - (v_a + 1) + 1 */
/* printf("w == %u, MAX[%u, %u]\n", w, v_a + 1, v_b - 1); */
				p = msb(w);
/*
printf("p == %u\n", p);
printf("MAX(%u, %u)\n", max_freq[p - 1][v_a + 1], max_freq[p - 1][v_b - (1 << (p - 1))]);
*/
				if ((f = MAX(max_freq[p - 1][v_a + 1], max_freq[p - 1][v_b - (1 << (p - 1))])) > max) max = f;
/* printf("f == %u\n", f); */
			}
			printf("%u\n", max);
		}
	}
	return 0;
}
