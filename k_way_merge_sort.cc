#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>

#define NUM_QUEUE 5000
#define NUM_ELEM 100

bool comp_uint(const unsigned int &a, const unsigned int &b) {
	return a < b;
}

template<typename T> class q_comp {
	public : 
		q_comp(bool (*const __comp)(const T &, const T &)) : comp(__comp) {}
		bool operator() (const std::pair<size_t, T> &a, const std::pair<size_t, T> &b) const {
			return (*comp)(a.second, b.second);
		}
	private :
		bool (*const comp)(const T&, const T&);
};

template <typename T> void k_way_merge_sort(const size_t K, std::priority_queue<T> q[], bool (*const comp)(const T &, const T &), std::list<T> &result) {
	q_comp<T> qc(comp);
	std::priority_queue< std::pair<size_t, T>, std::vector< std::pair<size_t, T> >, q_comp<T> > Q((q_comp<T>(comp)));
	for (size_t k = 0; k < K; ++k) {
		if (!q[k].empty()) {
			Q.push(std::pair<size_t, T>(k, q[k].top()));
			q[k].pop();
		}
	}
	while (!Q.empty()) {
		std::pair<size_t, T> c_p = Q.top();
		Q.pop();
		result.push_back(c_p.second);
		if (!q[c_p.first].empty()) {
			Q.push(std::pair<size_t, T>(c_p.first, q[c_p.first].top()));
			q[c_p.first].pop();
		}
	}
}

/* test case */
int main(int argc, char *argv[]) {
	unsigned int elem;
	std::priority_queue<unsigned int> q[NUM_QUEUE];
	std::list<unsigned int> result;
	std::list<unsigned int>::const_reverse_iterator r_iter;
	std::vector<unsigned int> expected_result; 
	std::vector<unsigned int>::const_iterator e_iter;
	srand(time(0));
	for (size_t k = 0; k < NUM_QUEUE; ++k) for (size_t n = 0; n < NUM_ELEM; ++n) elem = rand(), q[k].push(elem), expected_result.push_back(elem);
	std::sort(expected_result.begin(), expected_result.end(), comp_uint);
	k_way_merge_sort<unsigned int>(NUM_QUEUE, q, &comp_uint, result);
	assert(result.size() == expected_result.size());
	r_iter = result.rbegin();
	e_iter = expected_result.begin();
	while (r_iter != result.rend()) /*std::cout << *r_iter << " == " << *e_iter << std::endl, */assert(*r_iter++ == *e_iter++);
	return 0;
}
