#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#define MAX_LEN 256
#define ZERO "zero"

const char *const hundred = "derdnuh", *const lt_20[] = {"eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin", "net", "nevele", "evlewt", "neetriht", "neetruof", "neetfif", "neetxis", "neetneves", "neethgie", "neetenin"}, *const ge_20[] = {"ytnewt", "ytriht", "ytrof", "ytfif", "ytxis", "ytneves", "ythgie", "ytenin"}, *const powers_of_1000[] = {"dnasuoht", "noillim", "noillib", "noillirt", "noillirdauq", "noillitniuq"};
const unsigned int len_hundred = 7, len_lt_20[] = {3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 6, 6, 8, 8, 7, 7, 9, 8, 8}, len_ge_20[] = {6, 6, 5, 5, 5, 7, 6, 6}, len_powers_of_1000[] = {8, 7, 7, 8, 11, 11};

void append_space(char **const ptr) {
	**ptr = ' ', ++*ptr;
}

void read_lt_1000(const unsigned int N, char **const ptr) {
	unsigned int n, r, d;
	n = N;
	if ((r = n % 100)) {
		if (r < 20) strcpy(*ptr, lt_20[r - 1]), *ptr += len_lt_20[r - 1], append_space(ptr);
		else {
			if ((d = r % 10)) strcpy(*ptr, lt_20[d - 1]), *ptr += len_lt_20[d - 1], append_space(ptr);
			r /= 10, strcpy(*ptr, ge_20[r - 2]), *ptr += len_ge_20[r - 2], append_space(ptr);
		}
	}
	if (n /= 100) strcpy(*ptr, hundred), *ptr += len_hundred, append_space(ptr), strcpy(*ptr, lt_20[n - 1]), *ptr += len_lt_20[n - 1], append_space(ptr);
}



int main(int argc, char *argv[]) {
	unsigned int pk;
	uint64_t num;
	char ans[MAX_LEN + 1], *p;
	scanf("%"SCNu64, &num);
	if (!num) printf(ZERO);
	else {
		p = ans, pk = 0;
		while (1) {
			read_lt_1000(num % 1000, &p);
			if (num /= 1000) strcpy(p, powers_of_1000[pk]), p += len_powers_of_1000[pk], append_space(&p), ++pk; else break; 
		}
		for (--p; p != ans; putc(*--p, stdout));
	}
	putc('\n', stdout);
	return 0;
}
