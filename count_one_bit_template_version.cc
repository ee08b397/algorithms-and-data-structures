#include <iostream>
#include <climits>

template <typename T> unsigned int count_one_bit(const T n) {
	unsigned int w = 1;
	const size_t s = CHAR_BIT * sizeof(T);
	size_t r = s;
	T ones, mask, result = n;
	while (r >>= 1) {
		ones = ((T)1 << w) - 1; 
		mask = 0;
		for (size_t offset = 0; offset < s; offset += (w << 1)) {
			mask |= (ones << offset);
		}
		result = ((result & (mask << w)) >> w) + (result & mask);
		w <<= 1;
	}
	return result;
}

int main(int argc, char *argv[]) {
	std::cout << count_one_bit<char>(7) << "\n";
	std::cout << count_one_bit<short>(27) << "\n";
	std::cout << count_one_bit<int>(127) << "\n";
	std::cout << count_one_bit<unsigned int>(128) << "\n";
	std::cout << count_one_bit<long>(128) << "\n";
	std::cout << count_one_bit<unsigned long>(128) << "\n";
	std::cout << count_one_bit<long long>(129) << "\n";
	std::cout << count_one_bit<unsigned long long>(133) << "\n";
	std::cout << count_one_bit<unsigned char>(64) << "\n";
	std::cout << count_one_bit<long long>(0xFFFF0000) << "\n";
	std::cout << count_one_bit<unsigned long long>(0x0F0F00FF) << "\n";
	std::cout << count_one_bit<unsigned long long>(0xFFFF0000FFFF0000ull) << "\n";
	std::cout << count_one_bit<unsigned long long>(0xFFFFFFFFFFFF0000ull) << "\n";
	std::cout << count_one_bit<unsigned long long>(0xF0F0F0F0F0F0F0F0ull) << "\n";
	std::cout << count_one_bit<unsigned long long>(0x0000FFFF0000FFFFull) << "\n";
	std::cout << count_one_bit<unsigned long long>(0xFFFFFFFF0000FFFFull) << "\n";
	std::cout << count_one_bit<unsigned long long>(0xFFFFFFFFFFFFFFFFull) << "\n";
	return 0;
}
