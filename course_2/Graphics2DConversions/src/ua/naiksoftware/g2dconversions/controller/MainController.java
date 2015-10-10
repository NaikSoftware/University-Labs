package ua.naiksoftware.g2dconversions.controller;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.stage.FileChooser;
import javafx.util.Duration;
import ua.naiksoftware.g2dconversions.Context;
import ua.naiksoftware.g2dconversions.Parser;
import ua.naiksoftware.g2dconversions.model.Shape;

import javax.vecmath.Matrix3d;
import java.io.File;

public class MainController {

    @FXML
    private Canvas canvas;
    @FXML
    private Pane canvasWrapper;
    @FXML
    private ConversionsController conversionsController;

    private static final int FRAME_RATE = 20; //ms

    private FileChooser fileChooser;

    private Shape rootShape;
    private GraphicsContext graphics;
    private float cx, cy;
    private Matrix3d matrix;

    @FXML
    private void initialize() {
        fileChooser = new FileChooser();
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Supported", "*.svg")
        );
        graphics = canvas.getGraphicsContext2D();
        canvas.widthProperty().bind(canvasWrapper.widthProperty());
        canvas.heightProperty().bind(canvasWrapper.heightProperty());
        canvas.setOnMouseClicked(event -> {
            cx = (float) event.getX();
            cy = (float) event.getY();
            conversionsController.setCenter(cx, cy);
            redraw();
        });

        Timeline timeline = new Timeline(new KeyFrame(Duration.millis(FRAME_RATE), event -> {
            rootShape.transform(matrix);
            redraw();
        }));
        timeline.setCycleCount(Timeline.INDEFINITE);

        conversionsController.changeProperty().addListener((observable, oldValue, newValue) -> {
            matrix = newValue;
            if (rootShape != null) {
                if (newValue != null) timeline.play();
                else timeline.stop();
            }
        });
    }

    @FXML
    private void handleOpen(ActionEvent event) {
        File file = fileChooser.showOpenDialog(Context.getPrimaryStage());
        if (file == null) return;
        else fileChooser.setInitialDirectory(file.getParentFile());
        try {
            Parser.parse(file, shape -> {
                rootShape = shape;
                redraw();
                return null;
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void redraw() {
        graphics.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
        if (rootShape != null) rootShape.draw(graphics);
        graphics.setFill(Color.RED);
        graphics.fillOval(cx - 3, cy - 3, 6, 6);
    }

    @FXML
    private void handleAbout(ActionEvent event) {
        Context.loadToNewStage("About").showAndWait();
    }

    @FXML
    private void handleExit(ActionEvent event) {
        Platform.exit();
    }
}
