#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

template <typename T> class angle_comparator {
	public:
		bool operator () (const std::pair<T, double> &pt1, const std::pair<T, double> &pt2) const {
			return pt1.second < pt2.second;
		}
};

int main(int argc, char *argv[]) {
	size_t N;
	std::cin >> N;
	std::vector< std::pair< std::pair<double, double>, double > > pts;
	for (size_t n = 0; n < N; ++n) {
		double x, y;
		std::cin >> x >> y;
		pts.push_back(std::pair< std::pair<double, double>, double>(std::pair<double, double>(x, y), atan2(y, x)));
	}
	std::sort(pts.begin(), pts.end(), angle_comparator< std::pair<double, double> >());
	for (std::vector< std::pair< std::pair<double, double>, double> >::const_iterator iter = pts.begin(); iter != pts.end(); ++iter) { 
		std::cout << "(" << (iter -> first.first) << ", " << (iter -> first.second) << ")" << std::endl;
	}
	return 0;
}
