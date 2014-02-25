#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class circle : public shape {
	public :
		const double r;
		circle(const double __r) : r(__r) {} 
		~circle(){}
		double accept(const shape_visitor &) const;

};

#endif
