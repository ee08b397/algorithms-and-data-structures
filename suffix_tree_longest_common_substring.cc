#include <cstdio>
#include <cstring>

#define N_SYMB 128
#define NONE 0
#define LEAF 1
#define NON_LEAF 2

struct node {   /* d : depth (from starting point of the suffix) */
	size_t s, e, d;
	struct node *parent, *suffix_link, *next[N_SYMB];
};

void init_node(struct node *const n, const size_t s, const size_t e, const size_t d, node *const parent) {
	unsigned char i;
	n -> s = s;
	n -> e = e;
	n -> d = d;
	n -> parent = parent;
	n -> suffix_link = NULL;
	for (i = 0; i < N_SYMB; ++i) n -> next[i] = NULL;
}

int contains(const struct node *const n, const size_t d) {   /* check if a position is contained within a node */
	return d >= n -> d && d < n -> d + n -> e - n -> s;
}

class suffix_tree {

	public :

		suffix_tree(size_t __length, const unsigned char *const __str) : next_node_idx(1), length(__length), str(__str), nd(new struct node[(length << 1) + 1]) {  /* # of nodes is at most ( 2 * length + 1 ) */
			unsigned char c;
			int prev_state = NONE;
			size_t p, q, idx, current_depth, current_pos;
			struct node *current_node, *prev_node, *new_node;
			init_node(&nd[0], 0, 0, 0, NULL);
			nd[0].suffix_link = &nd[0];
			current_node = &nd[0];
			prev_node = NULL;
			for (p = 0, q = 0; q < length; ++q) {
				c = str[q];   /* character to be added to the suffix tree */
				for (; p <= q; ++p) {
					current_depth = q - p; 
					if (NON_LEAF != prev_state) for (current_node = (current_node -> suffix_link ? current_node -> suffix_link : current_node -> parent -> suffix_link), idx = p + current_node -> d; current_depth && !contains(current_node, current_depth - 1); current_node = current_node -> next[str[idx += current_node -> e - current_node -> s]]);
					if (!contains(current_node, current_depth)) {
						if (prev_node) prev_node -> suffix_link = current_node, prev_node = NULL;
						if (!current_node -> next[c]) {  /* case 1: simply adding leaf node to the suffix tree -- the added leaf node is automatically extended in subsequent iteration(s) */
							init_node(current_node -> next[c] = &nd[next_node_idx++], q, length, current_depth, current_node); 
							prev_state = LEAF;
						}else {
							current_node = current_node -> next[c];  /* node for current symbol already exists */
							prev_state = NON_LEAF;
							break;  /* current end point becomes next active point */
						}
					}else {   /* construct implicit node */
						current_pos = current_node -> s + current_depth - current_node -> d;
						if (str[current_pos] != c) {  /* a split is required */
							init_node(new_node = &nd[next_node_idx++], current_node -> s, current_pos, current_node -> d, current_node -> parent);
							init_node(new_node -> next[c] = &nd[next_node_idx++], q, length, current_depth, new_node);
							new_node -> next[str[current_pos]] = current_node;
							current_node -> parent -> next[str[current_node -> s]] = new_node;
							if (prev_node) prev_node -> suffix_link = new_node;
							current_node -> s = current_pos;
							current_node -> d = current_depth;
							current_node -> parent = new_node;
							current_node = prev_node = new_node;
							prev_state = LEAF;
						}else if (length != current_node -> e || current_node -> s < p + current_node -> d) {
							prev_state = NON_LEAF;
							break;  /* current end point becomes next active point */
						}else {
							prev_state = NONE;
						}
					}
				}
			}
			nd[0].suffix_link = NULL;
		}

		~suffix_tree() {
			delete [] nd;
		}

		/* traverse suffix tree to find longest common substring */
		static char *find_lcs(const size_t length1, const size_t length2, const char *const str1, const char *const str2, size_t &lcs_offset, size_t &lcs_length) {
			const size_t length = length1 + length2 + 2;
			char *const str = new char[length + 1];
			strcpy(str, str1);
			strcat(str, "\11");
			strcat(str, str2);
			strcat(str, "\12");
			lcs_offset = 0, lcs_length = 0;
			suffix_tree st(length, (const unsigned char *const)str);
			lcs(&st.nd[0], length1, length1 + 1 + length2, lcs_offset, lcs_length); 
			return str;
		}

		static unsigned int lcs(const node *const nd, const size_t offset1, const size_t offset2, size_t &lcs_offset, size_t &lcs_length) {
			if (nd -> s <= offset1 && offset1 < nd -> e) return 0x01;
			if (nd -> s <= offset2 && offset2 < nd -> e) return 0x10;
			unsigned int mask = 0x00;
			size_t current_length;
			for (unsigned char s = 0; s < N_SYMB; ++s) if (nd -> next[s]) mask |= lcs(nd -> next[s], offset1, offset2, lcs_offset, lcs_length)/*, printf("mask == %02x\n", mask)*/;
			current_length = nd -> d + nd -> e - nd -> s;
			if (0x11 == mask && current_length > lcs_length) {
				lcs_length = current_length; 
				lcs_offset = nd -> s - nd -> d;
			}
			return mask;
		}

	private : 
		size_t next_node_idx;
		const size_t length;
		const unsigned char *const str;
		struct node *const nd;

};

int main(int argc, char *argv[]) {
	size_t lcs_length, lcs_offset;
	/* const char *const str1 = "helloiamnotfrommississippiiamfrommaryland", *const str2 = "imissmississippi"; */
	/* const char *const str1 = "Hello, I am not from Mississippi. I am from Maryland.", *const str2 = "I miss Mississippi."; */
	const char *const str1 = "Hello, I am not from Mississippi. I am from Maryland.", *const str2 = "Hello, I missed a flight from Mississippi.";
	/* const char *const str1 = "Hello, I am not from Mississippi. I am from Maryland.", *const str2 = "Hello, I missed a flight from Maryland."; */
	/* const char *const str1 = "12345", *const str2 = "124234"; */
	/* const char *const str1 = "3312344112344333335", *const str2 = "13333231123444234"; */
	char *const str = suffix_tree::find_lcs(strlen(str1), strlen(str2), str1, str2, lcs_offset, lcs_length);
	/* printf("%lu, %lu\n", lcs_offset, lcs_length); */
	printf("%.*s\n", lcs_length, str + lcs_offset); 
	delete [] str;
	return 0;
}
