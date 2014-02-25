#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000000

int main(int argc, char *argv[]) {
	unsigned int wLen, pos, cnd;
	char W[MAX_LEN + 1];
	int T[MAX_LEN + 1];
	while (scanf("%s", W) != EOF) {
		if (W[0] == '.') {
			return 0;
		}
		wLen = strlen(W);
		T[0] = -1;
		T[1] = 0;
		pos = 2;
		cnd = 0;
		while (pos <= wLen) {
			if (W[pos - 1] == W[cnd]) {
				++cnd;
				T[pos++] = cnd;
			}else if (cnd) {
				cnd = T[cnd];
			}else {
				T[pos++] = 0;
			}
		}
		printf("%d\n", wLen % (wLen - T[wLen]) ? 1 : wLen / (wLen - T[wLen]));
	}
	return 0;
}
