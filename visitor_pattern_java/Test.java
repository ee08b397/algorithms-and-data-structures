package VisitorPattern;

public class Test {
	public static void main(String args[]) {
		AreaVisitor v = new AreaVisitor();
		Triangle t0 = new Triangle(1.0, 1.0, 0.0, 1.0, 0.0, 0.0);
		Triangle t1 = new Triangle(1.0, 2.0, 1.0, 4.0, 0.0, 3.0);
		Rectangle r = new Rectangle(4.0, 3.0);
		Circle c = new Circle(3.0);
		System.out.println(t0.accept(v));
		System.out.println(t1.accept(v));
		System.out.println(r.accept(v));
		System.out.println(c.accept(v));
	}
}
