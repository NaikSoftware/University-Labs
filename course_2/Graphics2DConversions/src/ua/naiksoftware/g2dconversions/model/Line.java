package ua.naiksoftware.g2dconversions.model;

import javafx.scene.canvas.GraphicsContext;

import javax.vecmath.Matrix3d;

/**
 * Created by N on 06.10.2015.
 */
public class Line extends Shape {

    private Point start, end;

    public Line(double x1, double y1, double x2, double y2) {
        start = new Point(x1, y1);
        end = new Point(x2, y2);
    }

    @Override
    public void transform(Matrix3d matrix) {
        start.transform(matrix);
        end.transform(matrix);
    }

    @Override
    public void draw(GraphicsContext graphicsContext) {
        graphicsContext.strokeLine(start.getX(), start.getY(), end.getX(), end.getY());
    }
}
