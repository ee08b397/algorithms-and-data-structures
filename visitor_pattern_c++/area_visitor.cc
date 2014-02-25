#include <cmath>
#include "area_visitor.h"

#ifdef DEBUGGING_OUTPUT
#include <iostream>
#endif

double area_visitor::visit(const triangle &t) const {
#ifdef DEBUGGING_OUTPUT
	std::cerr << "visiting triangle" << std::endl;
#endif
	return std::fabs(t.x1 * (t.y2 - t.y3) + t.x2 * (t.y3 - t.y1) + t.x3 * (t.x1 - t.x2)) / 2;
}

double area_visitor::visit(const rectangle &r) const {
#ifdef DEBUGGING_OUTPUT
	std::cerr << "visiting rectangle" << std::endl;
#endif
	return r.w * r.h;
}

double area_visitor::visit(const circle &c) const {
#ifdef DEBUGGING_OUTPUT
	std::cerr << "visiting circle" << std::endl;
#endif
	return PI * c.r * c.r;
}
