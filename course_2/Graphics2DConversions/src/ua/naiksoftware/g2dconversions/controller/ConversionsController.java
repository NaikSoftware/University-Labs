package ua.naiksoftware.g2dconversions.controller;

import com.sun.javafx.geom.Matrix3f;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.fxml.FXML;
import javafx.scene.control.Button;

import java.util.concurrent.Callable;

import static java.lang.Math.*;

/**
 * Created by N on 06.10.2015.
 */
public class ConversionsController {

    private static final float D = 5; // delta
    private static final double THETA = D * PI / 180;
    private static final float SCALE_FACTOR = 0.1f;

    @FXML
    private Button btnMoveRight, btnMoveLeft, btnMoveDown, btnMoveUp;
    @FXML
    private Button btnRotate;
    @FXML
    private Button btnScaleMinHoriz, btnScaleMaxHoriz, btnScaleMinVert, btnScaleMaxVert;

    private float cx, cy;
    private ObjectProperty<Matrix3f> changeProperty = new SimpleObjectProperty<>();

    @FXML
    private void initialize() {
        setupButton(btnMoveRight, () -> new Matrix3f(
                1, 0, 0,
                0, 1, 0,
                D, 0, 1
        ));
        setupButton(btnMoveLeft, () -> new Matrix3f(
                1, 0, 0,
                0, 1, 0,
                -D, 0, 1
        ));
        setupButton(btnMoveDown, () -> new Matrix3f(
                1, 0, 0,
                0, 1, 0,
                0, D, 1
        ));
        setupButton(btnMoveUp, () -> new Matrix3f(
                1, 0, 0,
                0, 1, 0,
                0, -D, 1
        ));
        setupButton(btnRotate, () -> new Matrix3f(
                (float) cos(THETA), (float) sin(THETA), 0,
                (float) -sin(THETA), (float) cos(THETA), 0,
                (float) (-cx * (cos(THETA) - 1) + cy * sin(THETA)), (float) (-cy * (cos(THETA) - 1) - cx * sin(THETA)), 1
        ));
        setupButton(btnScaleMinHoriz, () -> new Matrix3f(
                1 - SCALE_FACTOR, 0, 0,
                0, 1, 0,
                -(1 - SCALE_FACTOR) * cx + cx, 0, 1
        ));
        setupButton(btnScaleMaxHoriz, () -> new Matrix3f(
                1 + SCALE_FACTOR, 0, 0,
                0, 1, 0,
                -(1 + SCALE_FACTOR) * cx + cx, 0, 1
        ));
        setupButton(btnScaleMinVert, () -> new Matrix3f(
                1, 0, 0,
                0, 1 - SCALE_FACTOR, 0,
                0, -(1 - SCALE_FACTOR) * cy + cy, 1
        ));
        setupButton(btnScaleMaxVert, () -> new Matrix3f(
                1, 0, 0,
                0, 1 + SCALE_FACTOR, 0,
                0, -(1 + SCALE_FACTOR) * cy + cy, 1
        ));
    }

    public void setCenter(float cx, float cy) {
        this.cx = cx;
        this.cy = cy;
    }

    public ObjectProperty<Matrix3f> changeProperty() {
        return changeProperty;
    }

    private void setupButton(Button btn, Callable<Matrix3f> callable) {
        btn.setOnMousePressed(event -> { // TODO: handle hold button
            try {
                changeProperty().setValue(callable.call());
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }
}
