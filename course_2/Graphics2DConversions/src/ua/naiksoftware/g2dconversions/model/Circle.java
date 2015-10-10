package ua.naiksoftware.g2dconversions.model;

import com.sun.javafx.geom.Matrix3f;
import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import ua.naiksoftware.g2dconversions.Operation;

/**
 * Created by naik on 08.10.15.
 */
public class Circle extends Shape {

    private Point2D midLeft, midTop, midRight, midDown;
    private Point2D leftTop, rightTop, rightDown, leftDown;

    public Circle(float cx, float cy, float radius) {

        midLeft = new Point2D(cx - radius, cy);
        midTop = new Point2D(cx, cy - radius);
        midRight = new Point2D(cx + radius, cy);
        midDown = new Point2D(cx, cy + radius);
        leftTop = new Point2D(cx - radius, cy - radius);
        rightTop = new Point2D(cx + radius, cy - radius);
        rightDown = new Point2D(cx + radius, cy + radius);
        leftDown = new Point2D(cx - radius, cy + radius);
    }

    @Override
    public void transform(Matrix3f matrix) {
        midLeft = Operation.multiple(matrix, midLeft);
        midTop = Operation.multiple(matrix, midTop);
        midRight = Operation.multiple(matrix, midRight);
        midDown = Operation.multiple(matrix, midDown);

        leftTop = Operation.multiple(matrix, leftTop);
        rightTop = Operation.multiple(matrix, rightTop);
        rightDown = Operation.multiple(matrix, rightDown);
        leftDown = Operation.multiple(matrix, leftDown);
    }

    @Override
    public void draw(GraphicsContext graphicsContext) {
        graphicsContext.beginPath();
        graphicsContext.moveTo(midLeft.getX(), midLeft.getY());

        graphicsContext.quadraticCurveTo(midLeft.midpoint(leftTop).getX(), midLeft.midpoint(leftTop).getY(),
                midTop.getX(), midTop.getY());

        graphicsContext.moveTo(midLeft.getX(), midLeft.getY());
        graphicsContext.bezierCurveTo(midLeft.midpoint(leftTop).getX(), midLeft.midpoint(leftTop).getY(),
                leftTop.midpoint(midTop).getX(), leftTop.midpoint(midTop).getY(),
                midTop.getX(), midTop.getY());

        graphicsContext.bezierCurveTo(midTop.midpoint(rightTop).getX(), midTop.midpoint(rightTop).getY(),
                rightTop.midpoint(midRight).getX(), rightTop.midpoint(midRight).getY(),
                midRight.getX(), midRight.getY());

        graphicsContext.bezierCurveTo(midRight.midpoint(rightDown).getX(), midRight.midpoint(rightDown).getY(),
                rightDown.midpoint(midDown).getX(), rightDown.midpoint(midDown).getY(),
                midDown.getX(), midDown.getY());

        graphicsContext.bezierCurveTo(midDown.midpoint(leftDown).getX(), midDown.midpoint(leftDown).getY(),
                leftDown.midpoint(midLeft).getX(), leftDown.midpoint(midLeft).getY(),
                midLeft.getX(), midLeft.getY());

        graphicsContext.stroke();
    }
}
