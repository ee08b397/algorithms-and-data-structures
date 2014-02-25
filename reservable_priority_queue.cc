#include <cstdio>
#include <queue>
#include <vector>

#define MAX_N 100
#define MAX_M 100

class comp_2nd_coord {
	public :
		bool operator() (const std::pair<unsigned int, unsigned int> &a, const std::pair<unsigned int, unsigned int> &b) {
			return a.second > b.second;
		}
};


template < class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type> > class reservable_priority_queue: public std::priority_queue<T> {
	public:
		typedef typename std::priority_queue<T, Container, Compare>::size_type size_type;
		reservable_priority_queue(size_type capacity = 0) { reserve(capacity); };
		void reserve(const size_type capacity) { this -> c.reserve(capacity); } 
		size_type capacity() const { return this -> c.capacity(); } 
};


int main(int argc, char *argv[]) {
	return 0;
}
