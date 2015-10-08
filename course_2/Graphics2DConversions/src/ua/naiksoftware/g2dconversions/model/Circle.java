package ua.naiksoftware.g2dconversions.model;

import com.sun.javafx.geom.Matrix3f;
import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.shape.Arc;
import javafx.scene.shape.ArcType;
import ua.naiksoftware.g2dconversions.Operation;

/**
 * Created by naik on 08.10.15.
 */
public class Circle extends Shape {

    private Point2D cernLeft, cernTop, cernRight, cernDown;
    private Point2D curve1, curve2, curve3, curve4;

    public Circle(float cx, float cy, float radius) {
        cernLeft = new Point2D(cx - radius, cy);
        cernTop = new Point2D(cx, cy - radius);
        cernRight = new Point2D(cx + radius, cy);
        cernDown = new Point2D(cx, cy + radius);
        curve1 = new Point2D(cx - radius, cy - radius);
        curve2 = new Point2D(cx + radius, cy - radius);
        curve3 = new Point2D(cx + radius, cy + radius);
        curve4 = new Point2D(cx - radius, cy + radius);
    }

    @Override
    public void transform(Matrix3f matrix) {
        cernLeft = Operation.multiple(matrix, cernLeft);
        cernTop = Operation.multiple(matrix, cernTop);
        cernRight = Operation.multiple(matrix, cernRight);
        cernDown = Operation.multiple(matrix, cernDown);

        curve1 = Operation.multiple(matrix, curve1);
        curve2 = Operation.multiple(matrix, curve2);
        curve3 = Operation.multiple(matrix, curve3);
        curve4 = Operation.multiple(matrix, curve4);
    }

    @Override
    public void draw(GraphicsContext graphicsContext) {
        graphicsContext.beginPath();
        double deg = curve1.angle(cernLeft, cernTop);

        Arc arc = new Arc();
        arc.setCenterX(50.0f);
        arc.setCenterY(50.0f);
        arc.setRadiusX(25.0f);
        arc.setRadiusY(25.0f);
        arc.setStartAngle(45.0f);
        arc.setLength(270.0f);
        arc.setType(ArcType.OPEN);

        //System.out.println("Deg: " + deg);
        double angle = curve4.angle(curve1, curve4.add(0, -1));
        System.out.println(angle);
        graphicsContext.strokeArc(curve1.getX(), curve1.getY(), curve1.distance(curve2), curve1.distance(curve4), 90 - angle, 90, ArcType.ROUND);
        /*graphicsContext.quadraticCurveTo(curve1.getX(), curve1.getY(), cernTop.getX(), cernTop.getY());
        graphicsContext.quadraticCurveTo(curve2.getX(), curve2.getY(), cernRight.getX(), cernRight.getY());
        graphicsContext.quadraticCurveTo(curve3.getX(), curve3.getY(), cernDown.getX(), cernDown.getY());
        graphicsContext.quadraticCurveTo(curve4.getX(), curve4.getY(), cernLeft.getX(), cernLeft.getY());*/
        //graphicsContext.closePath();
        //graphicsContext.stroke();

        graphicsContext.strokeLine(curve1.getX(), curve1.getY(), curve2.getX(), curve2.getY());
        graphicsContext.strokeLine(curve1.getX(), curve1.getY(), curve4.getX(), curve4.getY());

        graphicsContext.strokeLine(cernLeft.getX(), cernLeft.getY(), cernRight.getX(), cernRight.getY());
        graphicsContext.strokeLine(cernTop.getX(), cernTop.getY(), cernDown.getX(), cernDown.getY());
    }
}
