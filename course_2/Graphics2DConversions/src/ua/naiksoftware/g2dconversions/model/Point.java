package ua.naiksoftware.g2dconversions.model;

import javax.vecmath.Matrix3d;

/**
 * Created by naik on 10.10.15.
 */
public class Point {

    private double x, y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public Point add(double x, double y) {
        return new Point(this.x + x, this.y + y);
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public void transform(Matrix3d m) {
        double tmp_x = x, tmp_y = y;
        x = tmp_x * m.m00 + tmp_y * m.m10 + m.m20;
        y = tmp_x * m.m01 + tmp_y * m.m11 + m.m21;
    }

    public static void transform(Matrix3d m, Point... points) {
        for (Point p : points) p.transform(m);
    }
}
