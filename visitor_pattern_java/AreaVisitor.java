package VisitorPattern;

public class AreaVisitor extends ShapeVisitor {
	protected double visit(final Triangle t) {
		return Math.abs(t.x1 * (t.y2 - t.y3) + t.x2 * (t.y3 - t.y1) + t.x3 * (t.x1 - t.x2)) / 2;
	}
	protected double visit(final Rectangle r) {
		return r.w * r.h;
	}
	protected double visit(final Circle c) {
		return Math.PI * c.r * c.r;
	}
}
