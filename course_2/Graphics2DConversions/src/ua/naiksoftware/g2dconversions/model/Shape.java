package ua.naiksoftware.g2dconversions.model;

import com.sun.javafx.geom.Matrix3f;
import javafx.scene.canvas.GraphicsContext;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Naik on 05.10.2015.
 */
public class Shape {

    private List<Shape> inners = new ArrayList<>();
    private double x, y;

    public List<Shape> getInners() {
        return inners;
    }

    public void addInner(Shape shape) {
        inners.add(shape);
    }

    public void transform(Matrix3f matrix) {
        inners.stream().forEach(shape -> shape.transform(matrix));
    }

    public void draw(GraphicsContext graphicsContext) {
        inners.stream().forEach(shape -> shape.draw(graphicsContext));
    }
}
