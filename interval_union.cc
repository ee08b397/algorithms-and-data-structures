#include <iostream>
#include <queue>

template <typename S, typename T> class ptComparator{
	public:
		bool operator() (const std::pair<S, T> &a, const std::pair<S, T> &b) const{
			return a.first > b.first || (a.first == b.first && a.second < b.second);
		}
};

int main(int argc, char *argv[]){
	unsigned int N, a, b, count = 0;
	std::priority_queue< std::pair<unsigned int, unsigned int>, std::vector< std::pair<unsigned int, unsigned int> >, ptComparator<unsigned int, unsigned int> > pt;
	std::cin>>N;
	while (N--){
		std::cin>>a>>b;
		pt.push(std::pair<unsigned int, unsigned int>(a, 1));
		pt.push(std::pair<unsigned int, unsigned int>(b, 0));
	}
	while (!pt.empty()){
		std::pair<unsigned int, unsigned int> p = pt.top();
		if (p.second){
			if (count == 0){
				std::cout<<p.first<<' ';
			}
			++count;
		}else{
			--count;
			if (count == 0){
				std::cout<<p.first<<'\n';
			}
		}
		pt.pop();
	}
	return 0;
}
