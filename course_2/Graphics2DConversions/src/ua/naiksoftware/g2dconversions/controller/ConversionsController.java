package ua.naiksoftware.g2dconversions.controller;

import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.input.MouseEvent;
import ua.naiksoftware.g2dconversions.util.Callable;

import javax.vecmath.Matrix3d;

import static java.lang.Math.*;

/**
 * Created by N on 06.10.2015.
 */
public class ConversionsController {

    private static final float D = 3; // delta
    private static final double THETA = D * PI / 180;
    private static final float SCALE_FACTOR = 0.1f;

    @FXML
    private Button btnMoveRight, btnMoveLeft, btnMoveDown, btnMoveUp;
    @FXML
    private Button btnRotate;
    @FXML
    private Button btnScaleMinHoriz, btnScaleMaxHoriz, btnScaleMinVert, btnScaleMaxVert;

    private double cx, cy;
    private ObjectProperty<Matrix3d> changeProperty = new SimpleObjectProperty<>();

    @FXML
    private void initialize() {
        setupButton(btnMoveRight, () -> new Matrix3d(
                1, 0, 0,
                0, 1, 0,
                D, 0, 1
        ));
        setupButton(btnMoveLeft, () -> new Matrix3d(
                1, 0, 0,
                0, 1, 0,
                -D, 0, 1
        ));
        setupButton(btnMoveDown, () -> new Matrix3d(
                1, 0, 0,
                0, 1, 0,
                0, D, 1
        ));
        setupButton(btnMoveUp, () -> new Matrix3d(
                1, 0, 0,
                0, 1, 0,
                0, -D, 1
        ));
        setupButton(btnRotate, () -> new Matrix3d(
                cos(THETA), sin(THETA), 0,
                -sin(THETA), cos(THETA), 0,
                -cx * (cos(THETA) - 1) + cy * sin(THETA), -cx * sin(THETA) - cy * (cos(THETA) - 1), 1
        ));
        setupButton(btnScaleMinHoriz, () -> new Matrix3d(
                1 - SCALE_FACTOR, 0, 0,
                0, 1, 0,
                -(1 - SCALE_FACTOR) * cx + cx, 0, 1
        ));
        setupButton(btnScaleMaxHoriz, () -> new Matrix3d(
                1 + SCALE_FACTOR, 0, 0,
                0, 1, 0,
                -(1 + SCALE_FACTOR) * cx + cx, 0, 1
        ));
        setupButton(btnScaleMinVert, () -> new Matrix3d(
                1, 0, 0,
                0, 1 - SCALE_FACTOR, 0,
                0, -(1 - SCALE_FACTOR) * cy + cy, 1
        ));
        setupButton(btnScaleMaxVert, () -> new Matrix3d(
                1, 0, 0,
                0, 1 + SCALE_FACTOR, 0,
                0, -(1 + SCALE_FACTOR) * cy + cy, 1
        ));
    }

    public void setCenter(double cx, double cy) {
        this.cx = cx;
        this.cy = cy;
    }

    public ObjectProperty<Matrix3d> changeProperty() {
        return changeProperty;
    }

    private void setupButton(Button btn, Callable<Matrix3d> callable) {
        btn.addEventHandler(MouseEvent.MOUSE_PRESSED, event -> changeProperty.set(callable.call()));
        btn.addEventHandler(MouseEvent.MOUSE_RELEASED, event -> changeProperty.set(null));
    }
}
