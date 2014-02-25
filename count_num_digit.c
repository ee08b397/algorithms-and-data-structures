#include <stdio.h>

void count(const int, const int, unsigned int []);

void count(const int n, const int dup, unsigned int num[]) {
	int unit_digit, m, rem, d;
	if (n <= 0) return;
	unit_digit = n % 10;
	m = n / 10;
	rem = m;
	for (d = 0; d <= unit_digit; ++d){   /* count the unit digits (0 through current unit digit) */
		num[d] += dup;
	}
	while (rem){   /* count occurrences of other digits while the unit digit varies from its current value to 0 */
		num[rem % 10] += (unit_digit + 1) * dup;
		rem /= 10;
	}
	num[0] += dup * (m - 1);  /* count occurrences of 0s at unit digit while non-unit digits are decreasing */
	for (d = 1; d < 10; ++d) { /* count occurrences of non-0s at unit digit while non-unit digits are decreasing */
		num[d] += dup * m;
	}
	count(m - 1, 10 * dup, num);  /* count all remaining */
}

int main(int argc, char *argv[]) { 
	unsigned int a, b, d, tmp, num_a[10], num_b[10];
	while (1) {
		scanf("%u%u", &a, &b);
		if (!a && !b) return 0;
		if (a > b) {
			tmp = a;
			a = b;
			b = tmp;
		}
		for (d = 0; d < 10; ++d) num_b[d] = num_a[d] = 0;
		count(b, 1, num_b);
		if (a) count(a - 1, 1, num_a);
		for (d = 0; d < 9; ++d) printf("%d ", num_b[d] - num_a[d]);
		printf("%d\n", num_b[9] - num_a[9]);
	}
	return 0;
}
