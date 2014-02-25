package VisitorPattern;

public class Triangle extends Shape {
	final double x1;
	final double y1;
	final double x2;
	final double y2;
	final double x3;
	final double y3;
	public Triangle(final double x1, final double y1, final double x2, final double y2, final double x3, final double y3) {
		this.x1 = x1;
		this.y1 = y1;
		this.x2 = x2;
		this.y2 = y2;
		this.x3 = x3;
		this.y3 = y3;
	}
	protected double accept(final ShapeVisitor visitor) {
		return visitor.visit(this);
	}
}
