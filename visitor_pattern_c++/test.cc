#include <iostream>
#include "area_visitor.h"

int main(int argc, char *argv[]) {
	area_visitor v;
	triangle t0(1.0, 1.0, 0.0, 1.0, 0.0, 0.0); 
	triangle t1(1.0, 2.0, 1.0, 4.0, 0.0, 3.0); 
	rectangle r(4.0, 3.0); 
	circle c(3.0);
	std::cout << t0.accept(v) << std::endl;
	std::cout << t1.accept(v) << std::endl;
	std::cout << r.accept(v) << std::endl;
	std::cout << c.accept(v) << std::endl;
	return 0;
}
