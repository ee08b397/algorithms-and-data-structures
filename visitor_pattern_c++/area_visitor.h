#ifndef AREA_VISITOR_H
#define AREA_VISITOR_H

#include <cmath>
#include "triangle.h"
#include "rectangle.h"
#include "circle.h"
#include "shape_visitor.h"

class area_visitor : public shape_visitor {

	public :
		double visit(const triangle &) const;
		double visit(const rectangle &) const;
		double visit(const circle &) const;
		area_visitor() {}

	private :
		const static double PI = 3.14159265358979323846; /* of course on POSIX platforms, one can just use the M_PI macro instead */
};

#endif
