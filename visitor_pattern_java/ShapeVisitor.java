package VisitorPattern;

public abstract class ShapeVisitor {
	protected abstract double visit(final Triangle t);
	protected abstract double visit(final Rectangle r);
	protected abstract double visit(final Circle c);
}
