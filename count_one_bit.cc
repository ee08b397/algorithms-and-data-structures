#include <iostream>

int count_one_bit(int n) {
	n = (n & 0x55555555) + ((n & 0xAAAAAAAA) >> 1);
	n = (n & 0x33333333) + ((n & 0xCCCCCCCC) >> 2);
	n = (n & 0x0F0F0F0F) + ((n & 0xF0F0F0F0) >> 4);
	n = (n & 0x00FF00FF) + ((n & 0xFF00FF00) >> 8); 
	n = (n & 0x0000FFFF) + ((n & 0xFFFF0000) >> 16);
	return n;
}

int main(int argc, char *argv[]) {
	std::cout << count_one_bit(7) << "\n";
	std::cout << count_one_bit(27) << "\n";
	std::cout << count_one_bit(127) << "\n";
	std::cout << count_one_bit(128) << "\n";
	std::cout << count_one_bit(128) << "\n";
	std::cout << count_one_bit(128) << "\n";
	std::cout << count_one_bit(129) << "\n";
	std::cout << count_one_bit(133) << "\n";
	std::cout << count_one_bit(64) << "\n";
	std::cout << count_one_bit(0xFFFF0000) << "\n";
	std::cout << count_one_bit(0x0F0F00FF) << "\n";
	return 0;
}
