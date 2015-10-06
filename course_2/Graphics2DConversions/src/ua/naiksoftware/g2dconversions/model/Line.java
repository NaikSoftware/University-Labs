package ua.naiksoftware.g2dconversions.model;

import com.sun.javafx.geom.Matrix3f;
import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;

/**
 * Created by N on 06.10.2015.
 */
public class Line extends Shape {

    private Point2D start, end;

    public Line(double x1, double y1, double x2, double y2) {
        start = new Point2D(x1, y1);
        end = new Point2D(x2, y2);
    }

    @Override
    public void transform(Matrix3f matrix) {
        // TODO: transform start and end points
        System.out.println("Transform: \n" + matrix);
    }

    @Override
    public void draw(GraphicsContext graphicsContext) {
        graphicsContext.strokeLine(start.getX(), start.getY(), end.getX(), end.getY());
    }
}
