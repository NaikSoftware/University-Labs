package ua.naiksoftware.g2dconversions.model;

import com.sun.javafx.geom.Matrix3f;
import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import ua.naiksoftware.g2dconversions.Operation;

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
        start = Operation.multiple(matrix, start);
        end = Operation.multiple(matrix, end);
    }

    @Override
    public void draw(GraphicsContext graphicsContext) {
        graphicsContext.strokeLine(start.getX(), start.getY(), end.getX(), end.getY());
    }
}
