/**
 * CubicCurve and structure of the applications taken from http://stackoverflow.com/a/13059212/2778639
 * QuadCurve added by me
 */

package sample;

import javafx.application.Application;
import javafx.beans.property.DoubleProperty;
import javafx.event.EventHandler;
import javafx.scene.*;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.*;
import javafx.stage.Stage;

/** Example of how a cubic curve works, drag the anchors around to change the curve. */
public class Main extends Application {
    public static void main(String[] args) throws Exception { launch(args); }
    @Override public void start(final Stage stage) throws Exception {

        CubicCurve cubicCurve = createCubicCurve();

        Line controlLine1 = new BoundLine(cubicCurve.controlX1Property(), cubicCurve.controlY1Property(), cubicCurve.startXProperty(), cubicCurve.startYProperty());
        Line controlLine2 = new BoundLine(cubicCurve.controlX2Property(), cubicCurve.controlY2Property(), cubicCurve.endXProperty(),   cubicCurve.endYProperty());

        Anchor start    = new Anchor(Color.PALEGREEN, cubicCurve.startXProperty(),    cubicCurve.startYProperty());
        Anchor control1 = new Anchor(Color.GOLD,      cubicCurve.controlX1Property(), cubicCurve.controlY1Property());
        Anchor control2 = new Anchor(Color.GOLDENROD, cubicCurve.controlX2Property(), cubicCurve.controlY2Property());
        Anchor end      = new Anchor(Color.TOMATO,    cubicCurve.endXProperty(),      cubicCurve.endYProperty());

        QuadCurve quadCurve = createQuadCurve();

        Anchor quadStart   = new Anchor(Color.CRIMSON,     quadCurve.startXProperty(), quadCurve.startYProperty());
        Anchor quadControl = new Anchor(Color.BURLYWOOD, quadCurve.controlXProperty(), quadCurve.controlYProperty());
        Anchor quadEnd     = new Anchor(Color.CORAL,     quadCurve.endXProperty(), quadCurve.endYProperty());

        stage.setTitle("Cubic Curve Manipulation Sample");
        stage.setScene(new Scene(new Group(controlLine1, controlLine2, cubicCurve, start, control1, control2, end,
                quadCurve, quadStart, quadControl, quadEnd), 800, 600, Color.ALICEBLUE));
        stage.show();
    }

    private QuadCurve createQuadCurve() {
        QuadCurve curve = new QuadCurve();
        curve.setStartX(400);
        curve.setStartY(100);
        curve.setControlX(450);
        curve.setControlY(50);
        curve.setEndX(600);
        curve.setEndY(200);
        curve.setStroke(Color.FORESTGREEN);
        curve.setStrokeWidth(4);
        curve.setStrokeLineCap(StrokeLineCap.ROUND);
        curve.setFill(Color.CORNSILK.deriveColor(0, 1.2, 1, 0.6));
        return curve;
    }

    private CubicCurve createCubicCurve() {
        CubicCurve curve = new CubicCurve();
        curve.setStartX(100);
        curve.setStartY(100);
        curve.setControlX1(150);
        curve.setControlY1(50);
        curve.setControlX2(250);
        curve.setControlY2(150);
        curve.setEndX(300);
        curve.setEndY(100);
        curve.setStroke(Color.FORESTGREEN);
        curve.setStrokeWidth(4);
        curve.setStrokeLineCap(StrokeLineCap.ROUND);
        curve.setFill(Color.CORNSILK.deriveColor(0, 1.2, 1, 0.6));
        return curve;
    }

    class BoundLine extends Line {
        BoundLine(DoubleProperty startX, DoubleProperty startY, DoubleProperty endX, DoubleProperty endY) {
            startXProperty().bind(startX);
            startYProperty().bind(startY);
            endXProperty().bind(endX);
            endYProperty().bind(endY);
            setStrokeWidth(2);
            setStroke(Color.GRAY.deriveColor(0, 1, 1, 0.5));
            setStrokeLineCap(StrokeLineCap.BUTT);
            getStrokeDashArray().setAll(10.0, 5.0);
        }
    }

    // a draggable anchor displayed around a point.
    class Anchor extends Circle {
        Anchor(Color color, DoubleProperty x, DoubleProperty y) {
            super(x.get(), y.get(), 10);
            setFill(color.deriveColor(1, 1, 1, 0.5));
            setStroke(color);
            setStrokeWidth(2);
            setStrokeType(StrokeType.OUTSIDE);

            x.bind(centerXProperty());
            y.bind(centerYProperty());
            enableDrag();
        }

        // make a node movable by dragging it around with the mouse.
        private void enableDrag() {
            final Delta dragDelta = new Delta();
            setOnMousePressed(new EventHandler<MouseEvent>() {
                @Override public void handle(MouseEvent mouseEvent) {
                    // record a delta distance for the drag and drop operation.
                    dragDelta.x = getCenterX() - mouseEvent.getX();
                    dragDelta.y = getCenterY() - mouseEvent.getY();
                    getScene().setCursor(Cursor.MOVE);
                }
            });
            setOnMouseReleased(new EventHandler<MouseEvent>() {
                @Override public void handle(MouseEvent mouseEvent) {
                    getScene().setCursor(Cursor.HAND);
                }
            });
            setOnMouseDragged(new EventHandler<MouseEvent>() {
                @Override public void handle(MouseEvent mouseEvent) {
                    double newX = mouseEvent.getX() + dragDelta.x;
                    if (newX > 0 && newX < getScene().getWidth()) {
                        setCenterX(newX);
                    }
                    double newY = mouseEvent.getY() + dragDelta.y;
                    if (newY > 0 && newY < getScene().getHeight()) {
                        setCenterY(newY);
                    }
                }
            });
            setOnMouseEntered(new EventHandler<MouseEvent>() {
                @Override public void handle(MouseEvent mouseEvent) {
                    if (!mouseEvent.isPrimaryButtonDown()) {
                        getScene().setCursor(Cursor.HAND);
                    }
                }
            });
            setOnMouseExited(new EventHandler<MouseEvent>() {
                @Override public void handle(MouseEvent mouseEvent) {
                    if (!mouseEvent.isPrimaryButtonDown()) {
                        getScene().setCursor(Cursor.DEFAULT);
                    }
                }
            });
        }

        // records relative x and y co-ordinates.
        private class Delta { double x, y; }
    }
}