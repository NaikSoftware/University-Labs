package ua.naiksoftware.g2dconversions.model;

import javafx.scene.canvas.GraphicsContext;

import javax.vecmath.Matrix3d;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Naik on 05.10.2015.
 */
public class Shape {

    private List<Shape> inners = new ArrayList<>();

    public List<Shape> getInners() {
        return inners;
    }

    public void addInner(Shape shape) {
        inners.add(shape);
    }

    public void transform(Matrix3d matrix) {
        inners.stream().forEach(shape -> shape.transform(matrix));
    }

    public void draw(GraphicsContext graphicsContext) {
        inners.stream().forEach(shape -> shape.draw(graphicsContext));
    }
}
