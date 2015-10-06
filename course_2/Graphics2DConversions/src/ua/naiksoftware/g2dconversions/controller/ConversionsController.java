package ua.naiksoftware.g2dconversions.controller;

import com.sun.javafx.geom.Matrix3f;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.fxml.FXML;
import javafx.scene.control.Button;

import java.util.concurrent.Callable;

/**
 * Created by N on 06.10.2015.
 */
public class ConversionsController {

    private static float D = 5; // delta

    @FXML
    private Button btnMoveRight;
    @FXML
    private Button btnMoveLeft;

    private double cx, cy;
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
    }

    public void setCenter(double cx, double cy) {
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
