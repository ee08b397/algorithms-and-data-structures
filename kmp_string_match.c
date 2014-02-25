#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 512

int main(int argc, char *argv[]) {
	/*
	    m: the beginning of the current match in S
	    i: the position of the current character in W
	    pos: index of entry to be computed in T
	    cnd: index of next character of the current candidate substring in W
	*/
	unsigned int m, i, sLen, wLen, pos, cnd, has_match;
	char S[MAX_INPUT_LEN + 1], W[MAX_INPUT_LEN + 1];
	int T[MAX_INPUT_LEN];
	while (1) {
		/* printf("S:\n"); */
		if (!fgets(S, MAX_INPUT_LEN, stdin)) {
			return 0;
		}
		/* printf("W:\n"); */
		fgets(W, MAX_INPUT_LEN, stdin);
		/* printf("S: %s\nW: %s\n", S, W); */
		sLen = strnlen(S, MAX_INPUT_LEN);
		if (sLen && S[sLen - 1] == '\n') {
			S[sLen - 1] = '\0';
			--sLen;
		}
		wLen = strnlen(W, MAX_INPUT_LEN);
		if (wLen && W[wLen - 1] == '\n') {
			W[wLen - 1] = '\0';
			--wLen;
		}

		/*
		 *  initialize both indexes to 0 
		 */
		m = 0;
		i = 0;

		/*
		    KMP table:
		    T[i] is the amount of backtrack required for finding the
		    next match if a mismatch at i-th character of W occurs
		 */
	
		/*
		    special case: mismatch at 1st char: no possibility of back-tracking
		*/
		T[0] = -1;
		/*
		    string of length 1 does not have any proper prefix
		 */
		T[1] = 0;
		pos = 2;
		cnd = 0;
		has_match = 0;
		while (pos <= wLen) {
			/*
			    1st case: the substring continues
			*/
			if (W[pos - 1] == W[cnd]) {
				++cnd;
				T[pos++] = cnd;
			}else if (cnd) {
			/*
			    2nd case: the substring does not continue, fall back required
			*/
				cnd = T[cnd];
			}else {
			/*
			    3rd case: cnd == 0, no candidate substring exists
			*/
				T[pos++] = 0;
			}
		}
	
		/*

		 for W == ABCDABD\0, output should be "-1 0 0 0 0 1 2 0"

		 for W == ABDDABD\0, output should be "-1 0 0 0 0 1 2 3"

		*/
	
		/*
		for (pos = 0; pos <= wLen; ++pos) {
			printf("%d\n", T[pos]);
		}
		*/

		while (m + i < sLen) { 
			/*
			    the i-th character of W matches
			 */  
			if (W[i] == S[m + i]) {
				/*
				     the entire pattern is matched
				 */
				if (i + 1 == wLen) {
					has_match = 1;
					printf("match found at S[%u]\n", m);
				}
				++i;
			}else {
				m += i - T[i];
				i = T[i] > -1 ? T[i] : 0;
			}
		}
		if (!has_match) {
			printf("no match found\n");
		}
		printf("\n");
	}
	return 0;
}
