#include <iostream>
#include <map>

unsigned int make_change(const unsigned int sum, const size_t N, const unsigned int *v, std::map<unsigned int, unsigned int> &chg_amnt, std::map<unsigned int, unsigned int> &num_chg) {
	if (sum == 0) {
		return 0;
	}
	std::map<unsigned int, unsigned int>::const_iterator c_iter = num_chg.find(sum);
	if (c_iter != num_chg.end()) { 
		return c_iter -> second;
	}
	unsigned int coin_val = 1, min_num_coin = 1 + make_change(sum - 1, N, v, chg_amnt, num_chg);
	for (unsigned int n = 0; n < N; ++n) {
		if (v[n] <= sum) {
			unsigned int num_coin = 1 + make_change(sum - v[n], N, v, chg_amnt, num_chg);
			if (num_coin < min_num_coin) { 
				min_num_coin = num_coin;
				coin_val = v[n];
			}
		}
	}
	chg_amnt.insert(std::pair<unsigned int, unsigned int>(sum, coin_val));
	num_chg.insert(std::pair<unsigned int, unsigned int>(sum, min_num_coin));
	return min_num_coin;
}

int main(int argc, char *argv[]) {
	unsigned int sum, N, *v;
	std::map<unsigned int, unsigned int> chg_amnt, num_chg;
	std::cin >> sum;
	std::cin >> N;
	v = new unsigned int[N];
	for (unsigned int n = 0; n < N; ++n) {
		std::cin >> v[n];
	}
	std::cout << make_change(sum, N, v, chg_amnt, num_chg) << std::endl;
	while (sum > 0) {
		unsigned int cval = chg_amnt[sum];
		std::cout << cval << ",";
		sum -= cval;
	}
	std::cout << "\n";
	delete [] v;
	return 0;
}
