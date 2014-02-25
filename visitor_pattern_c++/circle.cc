#include "circle.h"

#ifdef DEBUGGING_OUTPUT
#include <iostream>
#endif

double circle::accept(const shape_visitor &v) const {
#ifdef DEBUGGING_OUTPUT
	std::cerr << "circle::accept" << std::endl;
#endif
	return v.visit(*this);
}
