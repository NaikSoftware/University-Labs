package ua.naiksoftware.g2dconversions;

import com.sun.javafx.geom.Matrix3f;
import javafx.geometry.Point2D;

/**
 * Created by N on 07.10.2015.
 */
public class Operation {

    public static Point2D multiple(Matrix3f m, Point2D p) {
        double x = p.getX() * m.m00 + p.getY() * m.m10 + 1 * m.m20;
        double y = p.getX() * m.m01 + p.getY() * m.m11 + 1 * m.m21;
        return new Point2D(x, y);
    }
}
