#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class triangle : public shape {
	public :
		const double x1, y1, x2, y2, x3, y3;
		triangle(const double __x1, const double __y1, const double __x2, const double __y2, const double __x3, const double __y3) : x1(__x1), y1(__y1), x2(__x2), y2(__y2), x3(__x3), y3(__y3) {}
		~triangle() {}
		double accept(const shape_visitor &) const;
};

#endif
