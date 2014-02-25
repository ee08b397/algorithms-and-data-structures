package VisitorPattern;

public class Circle extends Shape {
	public final double r;
	public Circle(final double r) {
		this.r = r;
	}
	protected double accept(final ShapeVisitor visitor) {
		return visitor.visit(this);
	}
}
