#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class rectangle : public shape {
	public :
		const double w, h;
		rectangle(const double __w, const double __h) : w(__w), h(__h) {}
		~rectangle(){}
		double accept(const shape_visitor &) const;
};

#endif
