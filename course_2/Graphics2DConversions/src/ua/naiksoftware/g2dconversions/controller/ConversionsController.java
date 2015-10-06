package ua.naiksoftware.g2dconversions.controller;

import com.sun.javafx.geom.Matrix3f;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.fxml.FXML;
import ua.naiksoftware.g2dconversions.model.Shape;

/**
 * Created by N on 06.10.2015.
 */
public class ConversionsController {

    private double cx, cy;
    private Shape shape;
    private ObjectProperty<Matrix3f> changeProperty = new SimpleObjectProperty<>();

    @FXML
    private void initialize() {

    }

    public void setShape(Shape shape) {
        this.shape = shape;
    }

    public void setCenter(double cx, double cy) {
        this.cx = cx;
        this.cy = cy;
    }

    public ObjectProperty<Matrix3f> changeProperty() {
        return changeProperty;
    }

}
