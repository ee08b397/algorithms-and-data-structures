#include "rectangle.h"

#ifdef DEBUGGING_OUTPUT
#include <iostream>
#endif

double rectangle::accept(const shape_visitor &v) const {
#ifdef DEBUGGING_OUTPUT
	std::cerr << "rectangle::accept" << std::endl;
#endif
	return v.visit(*this);
}
