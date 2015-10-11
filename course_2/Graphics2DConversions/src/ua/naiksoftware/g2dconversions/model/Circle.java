package ua.naiksoftware.g2dconversions.model;

import javafx.scene.canvas.GraphicsContext;

import javax.vecmath.Matrix3d;

/**
 * Created by naik on 08.10.15.
 */
public class Circle extends Shape {

    private Point midLeft, midTop, midRight, midDown;
    private Point ctrl1, ctrl2, ctrl3, ctrl4, ctrl5, ctrl6, ctrl7, ctrl8;

    public Circle(double cx, double cy, double radius) {

        midLeft = new Point(cx - radius, cy);
        midTop = new Point(cx, cy - radius);
        midRight = new Point(cx + radius, cy);
        midDown = new Point(cx, cy + radius);

        double L = radius * 4f / 3 * Math.tan(Math.PI / 8);

        ctrl1 = midLeft.add(0, -L);
        ctrl2 = midTop.add(-L, 0);
        ctrl3 = midTop.add(L, 0);
        ctrl4 = midRight.add(0, -L);
        ctrl5 = midRight.add(0, L);
        ctrl6 = midDown.add(L, 0);
        ctrl7 = midDown.add(-L, 0);
        ctrl8 = midLeft.add(0, L);
    }

    @Override
    public void transform(Matrix3d matrix) {
        Point.transform(matrix, midLeft, midTop, midRight, midDown,
                ctrl1, ctrl2, ctrl3, ctrl4, ctrl5, ctrl6, ctrl7, ctrl8);
    }

    @Override
    public void draw(GraphicsContext graphicsContext) {
        graphicsContext.beginPath();
        graphicsContext.moveTo(midLeft.getX(), midLeft.getY());

        graphicsContext.bezierCurveTo(ctrl1.getX(), ctrl1.getY(), ctrl2.getX(), ctrl2.getY(),
                midTop.getX(), midTop.getY());

        graphicsContext.bezierCurveTo(ctrl3.getX(), ctrl3.getY(), ctrl4.getX(), ctrl4.getY(),
                midRight.getX(), midRight.getY());

        graphicsContext.bezierCurveTo(ctrl5.getX(), ctrl5.getY(), ctrl6.getX(), ctrl6.getY(),
                midDown.getX(), midDown.getY());

        graphicsContext.bezierCurveTo(ctrl7.getX(), ctrl7.getY(), ctrl8.getX(), ctrl8.getY(),
                midLeft.getX(), midLeft.getY());

        graphicsContext.stroke();
    }
}
