#include <stdio.h>
#include <string.h>

#define UNION 'U'
#define INTERSECTION 'I'
#define DIFF 'D'
#define REVERSE_DIFF 'C'
#define SYM_DIFF 'S'
#define INCL_L '['
#define EXCL_L '('
#define INCL_R ']'
#define EXCL_R ')'
#define MAX_CL 8
#define MAX_IL 16
#define MAX_N 131072
#define MAX_NUM_BYTE 16384

unsigned int N, ans[MAX_N][2];
unsigned char u[MAX_NUM_BYTE << 2], v[MAX_NUM_BYTE << 2], x[MAX_NUM_BYTE << 2];

void st(const unsigned int idx, const unsigned char val, unsigned char *const m) {
	if (val) m[idx >> 3] |= (1 << (idx & 7)); else m[idx >> 3] &= ~(1 << (idx & 7)); 
}

unsigned char ld(const unsigned int idx, const unsigned char *const m) {
	return (m[idx >> 3] >> (idx & 7)) & 1;
}

void push_down(const unsigned int node_num, const unsigned int min, const unsigned int max) {
	unsigned int val;
	if (min >= max) return;
	if (ld(node_num, u)) val = ld(node_num, v), st(node_num, 0, u), st(node_num << 1, 1, u), st((node_num << 1) | 1, 1, u), st(node_num << 1, 0, x), st((node_num << 1) | 1, 0, x), st(node_num << 1, val, v), st((node_num << 1) | 1, val, v);
	if (ld(node_num, x)) {
		if (ld(node_num << 1, u)) st(node_num << 1, ld(node_num << 1, v) ^ 1, v); else st(node_num << 1, ld(node_num << 1, x) ^ 1, x);
		if (ld((node_num << 1) | 1, u)) st((node_num << 1) | 1, ld((node_num << 1) | 1, v) ^ 1, v); else st((node_num << 1) | 1, ld((node_num << 1) | 1, x) ^ 1, x);
		st(node_num, 0, x); 
	}
}

void update(const unsigned int op, const unsigned int node_num, const unsigned int min, const unsigned int max, const unsigned int A, const unsigned int B, const unsigned char val) {
	unsigned int mid;
	push_down(node_num, min, max);
	if (min > max || max < A || min > B) return;
	if (min >= A && max <= B) {
		if (op) st(node_num, 1, u), st(node_num, val, v), st(node_num, 0, x); else if (ld(node_num, u)) st(node_num, ld(node_num, v) ^ 1, v); else st(node_num, 1, x);
		return;
	}
	if (min < max) mid = (min + max) >> 1, update(op, node_num << 1, min, mid, A, B, val), update(op, (node_num << 1) | 1, mid + 1, max, A, B, val);
}

void query(const unsigned int node_num, const unsigned int min, const unsigned int max) {
	unsigned int mid;
	if (min > max) return;
	push_down(node_num, min, max);
	if (ld(node_num, u)) {
		if (ld(node_num, v)) ans[N][0] = min, ans[N][1] = max, ++N;
		return;
	}
	if (ld(node_num, x)) {
		ans[N][0] = min, ans[N][1] = max, ++N;
		return;
	}
	if (min < max) mid = (min + max) >> 1, query(node_num << 1, min, mid), query((node_num << 1) | 1, mid + 1, max); 
}

int main(int argc, char *argv[]) {
	unsigned int A, B, i;
	char c[MAX_CL + 1], interval[MAX_IL + 1];
	N = 0, memset(u, 0, sizeof(u)), memset(v, 0, sizeof(v)), memset(x, 0, sizeof(x));
	while (EOF != scanf("%s%s", c, interval)) {
		for (A = 0, i = 1; interval[i] >= '0' && interval[i] <= '9'; ++i) A *= 10, A += interval[i] - '0';
		while (interval[i] < '0' || interval[i] > '9') ++i;
		for (B = 0; interval[i] >= '0' && interval[i] <= '9'; ++i) B *= 10, B += interval[i] - '0';
		if ((!B && INCL_R != interval[i]) || (A <<= 1, A += INCL_L == interval[0] ? 0 : 1) > (B <<= 1, B += (INCL_R == interval[i] ? 1 : 0) - 1)) continue;
		if (UNION == c[0]) update(1, 1, 0, (MAX_N << 1) - 1, A, B, 1); 
		else if (INTERSECTION == c[0]) {
			if (A) update(1, 1, 0, (MAX_N << 1) - 1, 0, A - 1, 0);
			if (B + 2 < (MAX_N << 1)) update(1, 1, 0, (MAX_N << 1) - 1, B + 1, (MAX_N << 1) - 1, 0);
		}else if (DIFF == c[0]) update(1, 1, 0, (MAX_N << 1) - 1, A, B, 0);
		else if (REVERSE_DIFF == c[0]) {
			update(0, 1, 0, (MAX_N << 1) - 1, 0, (MAX_N << 1) - 2, 1);
			if (A) update(1, 1, 0, (MAX_N << 1) - 1, 0, A - 1, 0);
			if (B + 2 < (MAX_N << 1)) update(1, 1, 0, (MAX_N << 1) - 1, B + 1, (MAX_N << 1) - 1, 0);
		}else update(0, 1, 0, (MAX_N << 1) - 1, A, B, 1);
	}
	query(1, 0, (MAX_N << 1) - 1);
	if (!N) printf("empty set\n"); else {
		printf("%c%u", ans[0][0] & 1 ? EXCL_L : INCL_L, ans[0][0] >> 1);
		for (i = 1; i < N; ++i) if (ans[i][0] > ans[i - 1][1] + 1) printf(",%u%c", (ans[i - 1][1] + 1) >> 1, ans[i - 1][1] & 1 ? EXCL_R : INCL_R), printf(" %c%u", ans[i][0] & 1 ? EXCL_L : INCL_L, ans[i][0] >> 1);
		printf(",%u%c\n", (ans[N - 1][1] + 1) >> 1, ans[N - 1][1] & 1 ? EXCL_R : INCL_R);
	}
	return 0;
}
