package VisitorPattern;

import VisitorPattern.ShapeVisitor;

public abstract class Shape {
	protected abstract double accept(final ShapeVisitor visitor);
}
