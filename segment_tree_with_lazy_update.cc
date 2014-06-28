#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <climits>

template <typename T, T OUT_OF_RANGE_ELEM> class sTree {

	public :

		sTree(const size_t __size, const T data[]) : size(__size), max_num_node(1 << (1 + ceil_log2(__size))), tree(new T[max_num_node]), delta(new T[max_num_node]) {
			if (size) {
				for (size_t n = 0; n < max_num_node; ++n) {
					delta[n] = 0;
				}
				init_tree(data, 1, 0, size - 1);
			}
		}

		void update(const size_t start, const size_t end, const T diff) {
			if (size) {
				update(1, 0, size - 1, start, end, diff);
			}
		}
		
		T query(const size_t start, const size_t end) { 
			if (size) {
				return query(1, 0, size - 1, start, end);
			}
			throw std::out_of_range("");
			return 0;
		}

		~sTree() {
			delete [] tree;
			delete [] delta;
		}

	private :

		const size_t size, max_num_node;
		T *const tree, *delta;

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
				unsigned int k = (((x & t[i]) == 0) ? 0 : j);
				y += k;
				x >>= k;
				j >>= 1;
			}

			return y;
		}

		void init_tree(const T data[], const size_t node_num, const size_t min_idx, const size_t max_idx) {
			if (min_idx > max_idx) return; /* range is empty */
			if (min_idx == max_idx) {  /* reaching leaf node of the tree */
				tree[node_num - 1] = data[min_idx];    /* initialize leaf value */
				return;
			}
			init_tree(data, node_num << 1, min_idx, (min_idx + max_idx) >> 1);   /* initialize left sub-tree */
			init_tree(data, (node_num << 1) + 1, 1 + ((min_idx + max_idx) >> 1), max_idx);   /* initialize right sub-tree*/
			tree[node_num - 1] = push_up(node_num);   /* up-propagate max value */
		}

		void update(const size_t node_num, const size_t min_idx, const size_t max_idx, const size_t start, const size_t end, const T diff) {
			push_down(node_num, min_idx, max_idx);
			if (min_idx > max_idx || max_idx < start || min_idx > end) return;  /* range is empty or disjoint from [start, end] */
			if (min_idx >= start && max_idx <= end) {  /* range is entirely contained in [start, end] */
				tree[node_num - 1] += diff;
				if (min_idx != max_idx) {   /* current node is not a leaf node */
					delta[(node_num << 1) - 1] += diff;
					delta[node_num << 1] += diff;
				}
				return;
			}
			update(node_num << 1, min_idx, (min_idx + max_idx) >> 1, start, end, diff);  /* update left sub-tree */
			update(1 + (node_num << 1), 1 + ((min_idx + max_idx) >> 1), max_idx, start, end, diff); /* Updating right child */
			tree[node_num - 1] = push_up(node_num); /* update root with max value */
		}

		T query(const size_t node_num, const size_t min_idx, const size_t max_idx, const size_t start, const size_t end) {
			
			if (min_idx > max_idx || max_idx < start || min_idx > end) return OUT_OF_RANGE_ELEM;   /* range is empty or disjoint from [start, end] */
			push_down(node_num, min_idx, max_idx);
			if (min_idx >= start && max_idx <= end) return tree[node_num - 1];  /* range is entirely contained in [start, end] */
			return aggregate(query(node_num << 1, min_idx, (min_idx + max_idx) >> 1, start, end), query(1 + (node_num << 1), 1 + ((min_idx + max_idx) >> 1), max_idx, start, end));  /* return max of max value from left sub-tree and max value from right sub-tree as final result */
		}

		void push_down(const size_t node_num, const size_t min_idx, const size_t max_idx) {
			if (delta[node_num - 1]) {
				tree[node_num - 1] += delta[node_num - 1];
				if (min_idx != max_idx) {    /* current node is not a leaf node */
					delta[(node_num << 1) - 1] += delta[node_num - 1];
					delta[node_num << 1] += delta[node_num - 1];
				}
				delta[node_num - 1] = 0;
			}
		}

		T aggregate(const T &a, const T &b) {
			return std::max(a, b);
		}

		T push_up(const size_t node_num) {
			return aggregate(tree[(node_num << 1) - 1], tree[node_num << 1]); 
		}
};

bool comp(const std::pair<size_t, int>& t1, const std::pair<size_t, int>& t2) {
	return t1.second < t2.second;
}

int main(int argc, char *argv[]) {
	size_t T;
	int *d;
	unsigned int *m, *r;
	std::pair<size_t, int> *ord; 
	std::cin >> T;
	d = new int[T];
	m = new unsigned int[T];
	r = new unsigned int[T];
	ord = new std::pair<size_t, int>[T];
	for (size_t t = 0; t < T; ++t) {
		ord[t].first = t;
		std::cin >> ord[t].second >> m[t];
	}
	std::sort(ord, ord + T, comp);
	for (size_t t = 0; t < T; ++t) {
		r[ord[t].first] = t;
		d[t] = -ord[t].second;
	}
	sTree<int, INT_MIN> s_tree(T, d);
	for (size_t t = 0; t < T; ++t) {
		s_tree.update(r[t], T - 1, m[t]);
		std::cout << std::max(s_tree.query(0, T - 1), 0) << std::endl;
	}
	delete [] d;
	delete [] m;
	delete [] r;
	delete [] ord;
	return 0;
}
