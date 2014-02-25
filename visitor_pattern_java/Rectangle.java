package VisitorPattern;

public class Rectangle extends Shape {
	final double w;
	final double h;
	public Rectangle(final double w, final double h) {
		this.w = w;
		this.h = h;
	}
	protected double accept(final ShapeVisitor visitor) {
		return visitor.visit(this);
	}
}
