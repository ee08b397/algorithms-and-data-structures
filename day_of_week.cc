#include <iostream>

const char * wd[] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};

const char * to_str(unsigned int w) {
	return wd[w];
}

unsigned int day_of_week(const int y, const int m, const int d) {
	int M = m == 1 ? 11 : m == 2 ? 12 : m - 2;
	return (d % 7 + (int)(2.6 * M - 0.2) % 7 + (5 * ((m < 3 ? y + 3 : y) % 4)) % 7 + (4 * ((m < 3 ? y + 99 : y) % 100)) % 7 + (6 * ((m < 3 ? y + 399 : y) % 400)) % 7) % 7;
}

int main(int argc, char *argv[]) {
	/*
	std::cout << day_of_week(2000, 1, 1) << std::endl;
	std::cout << day_of_week(2000, 12, 31) << std::endl;
	std::cout << day_of_week(1777, 4, 30) << std::endl;
	std::cout << day_of_week(1582, 10, 4) << std::endl;
	std::cout << day_of_week(0, 1, 1) << std::endl;
	std::cout << to_str(day_of_week(2003, 5, 25)) << std::endl;
	*/
	int y, m ,d;
	std::cin >> y >> m >> d;
	std::cout << to_str(day_of_week(y, m, d)) << std::endl;
	return 0;
}
