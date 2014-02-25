#include "triangle.h"

#ifdef DEBUGGING_OUTPUT
#include <iostream>
#endif

double triangle::accept(const shape_visitor &v) const {
#ifdef DEBUGGING_OUTPUT
	std::cerr << "triangle::accept" << std::endl;
#endif
	return v.visit(*this);
}
