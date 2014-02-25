#include <stdio.h>

#define MAX_N 1000000
#define MAX_W 10

int a[MAX_N], ans[MAX_N], decr_queue[MAX_N + MAX_W], incr_queue[MAX_N + MAX_W];

int main(int argc, char *argv[]) {
	int n, len, i, decr_queue_head, decr_queue_tail, incr_queue_head, incr_queue_tail;
	scanf("%u%u", &n, &len);
	for (i = 0; i < n; ++i) scanf("%d", &a[i]);
	incr_queue_head = incr_queue_tail = 0; incr_queue[0] = 0;
	decr_queue_head = decr_queue_tail = 0; decr_queue[0] = 0;
	if (len == 1) printf("%d ", a[0]);
	ans[0] = a[0];
	for (i = 1; i < n; ++i) {
		while (a[i] <= a[incr_queue[incr_queue_tail]] && incr_queue_tail >= incr_queue_head) --incr_queue_tail;
		incr_queue[++incr_queue_tail] = i;
		while (a[i] >= a[decr_queue[decr_queue_tail]] && decr_queue_tail >= decr_queue_head) --decr_queue_tail;
		decr_queue[++decr_queue_tail] = i;
		if (len <= i - incr_queue[incr_queue_head]) ++incr_queue_head;
		if (len <= i - decr_queue[decr_queue_head]) ++decr_queue_head;
		if (i + 1 >= len) printf("%d ", a[incr_queue[incr_queue_head]]);
		ans[i] = a[decr_queue[decr_queue_head]];
	}
	printf("\n");
	for (i = len - 1; i < n; ++i) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}
