#ifndef SHAPE_H
#define SHAPE_H

#include "shape_visitor.h"

class shape_visitor;

class shape {
	public :
		virtual double accept(const shape_visitor &v) const = 0;
};

#endif
