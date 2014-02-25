#ifndef SHAPE_VISITOR_H
#define SHAPE_VISITOR_H

/*
#define DEBUGGING_OUTPUT
*/

class triangle;
class rectangle;
class circle; 

class shape_visitor {

	public : 
		virtual double visit(const triangle &) const = 0;
		virtual double visit(const rectangle &) const = 0;
		virtual double visit(const circle &) const = 0;

	protected :
		shape_visitor() {}
};

#endif
