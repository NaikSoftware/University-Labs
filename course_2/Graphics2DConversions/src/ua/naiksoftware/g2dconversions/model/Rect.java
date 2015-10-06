package ua.naiksoftware.g2dconversions.model;

/**
 * Created by N on 06.10.2015.
 */
public class Rect extends Shape {

    public Rect(double x, double y, double w, double h) {
        addInner(new Line(x, y, x + w, y));
        addInner(new Line(x + w, y, x + w, y + h));
        addInner(new Line(x + w, y + h, x, y + h));
        addInner(new Line(x, y + h, x, y));
    }
}
