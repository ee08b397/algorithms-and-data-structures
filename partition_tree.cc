#include <cstdio>
#include <algorithm>

template <typename T> class partition_tree {

	public :

		partition_tree(const size_t __N, const T *const arr) : N(__N), max_depth(ceil_log2(__N) + 2), num_left(new size_t *[max_depth]), sorted(new T[__N + 1]), tree(new T*[max_depth]) {
			for (size_t d = 0; d < max_depth; ++d) tree[d] = new T[N + 1], num_left[d] = new size_t[N + 1];
			for (size_t p = 0; p < N; ++p) tree[0][p + 1] = sorted[p + 1] = arr[p];
			std::sort(sorted + 1, sorted + 1 + N, cmp);
			init(0, 1, N);
		}

		~partition_tree() {
			delete [] sorted;
			for (size_t d = 0; d < max_depth; ++d) delete [] tree[d], delete [] num_left[d];
			delete [] tree;
			delete [] num_left;
		}

		T query(const size_t min_query_idx, const size_t max_query_idx, const size_t k) const {
			return query(0, 1, N, min_query_idx, max_query_idx, k);
		}

	private :

		const size_t N, max_depth;	

		/* num_left[i][j] : number of element(s) less than median among the first j elements in the i-th layer of the tree  */
		size_t **const num_left;

		/* sorted: the original input sorted in ascending order */
		T *const sorted, **const tree;

		static bool cmp(const T &a, const T &b) {
			return a < b;
		}

		static unsigned int ceil_log2(const unsigned long long __x) {
			static const unsigned long long t[6] = {
				0xFFFFFFFF00000000ull,
				0x00000000FFFF0000ull,
				0x000000000000FF00ull,
				0x00000000000000F0ull,
				0x000000000000000Cull,
				0x0000000000000002ull
			};
		
			unsigned long long x = __x;
			unsigned int y = (((x & (x - 1)) == 0) ? 0 : 1);
		
			for (unsigned int j = 0x20, i = 0; i < 6; ++i) {
				int k = (((x & t[i]) == 0) ? 0 : j);
				y += k;
				x >>= k;
				j >>= 1;
			}

			return y;
		}

		/* initialize values in the $depth -th level of the tree with index(es) in range [start, end] */
		/* median_freq : number of times the median occurs in input array */
		void init(const size_t depth, const size_t start, const size_t end) {
			size_t mid = ((start + end) >> 1), l_idx = start, r_idx = mid + 1, median_freq = mid + 1 - start, p;
			for (p = start; p <= mid; ++p) if (sorted[p] < sorted[mid]) --median_freq; 
			for (p = start; p <= end; ++p) {
				num_left[depth][p] = (p == start ? 0 : num_left[depth][p - 1]);
				/* split current level of the tree with the median (with the 2 halves being "as equally as possible") */
				if (tree[depth][p] == sorted[mid]) {
					if (median_freq) --median_freq, ++num_left[depth][p], tree[depth + 1][l_idx++] = tree[depth][p]; else tree[depth + 1][r_idx++] = tree[depth][p];
				}else if (tree[depth][p] < sorted[mid]) ++num_left[depth][p], tree[depth + 1][l_idx++] = tree[depth][p]; else tree[depth + 1][r_idx++] = tree[depth][p];
			}
			if (start < end) {
				init(depth + 1, start, mid);
				init(depth + 1, mid + 1, end);
			}
		}

		/* returns the k-th largest element among all elements with index(es) in [min_query_idx, max_query_idx] in the input array */
		T query(const size_t depth, const size_t start, const size_t end, const size_t min_query_idx, const size_t max_query_idx, const size_t k) const {
			size_t s, ss, mid = ((start + end) >> 1);
			if (start == end) return tree[depth][start];
			if (start == min_query_idx) s = 0, ss = num_left[depth][max_query_idx]; /* <-- special case */ else s = num_left[depth][min_query_idx - 1], ss = num_left[depth][max_query_idx] - s;
			return ss >= k ? query(depth + 1, start, mid, start + s, start + s + ss - 1, k) : query(depth + 1, mid + 1, end, mid + 1 + min_query_idx - start - s, mid + 1 + max_query_idx - start - s - ss, k - ss);
		}

};

/* test cases */
#define MAX_N 100000

int arr[MAX_N];

int main(int argc, char *argv[]) {
	unsigned int n, m, p, l, r, k;
	scanf("%u%u", &n, &m);
	for (p = 0; p < n; ++p) scanf("%d", &arr[p]);
	partition_tree<int> pt(n, arr); 
	while (m--) {
		scanf("%u%u%u", &l, &r, &k);
		printf("%d\r\n", pt.query(l, r, k));
	}
	return 0;
}
