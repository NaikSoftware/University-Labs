package ua.naiksoftware.g2dconversions.controller;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.FillRule;
import javafx.stage.FileChooser;
import ua.naiksoftware.g2dconversions.Context;
import ua.naiksoftware.g2dconversions.Parser;
import ua.naiksoftware.g2dconversions.model.Shape;

import java.io.File;

public class MainController {

    @FXML
    private Canvas canvas;
    @FXML
    private Pane canvasWrapper;

    private FileChooser fileChooser;
    private File file;

    private Shape rootShape;
    private GraphicsContext graphics;
    private static final Color BG = Color.AZURE;

    @FXML
    private void initialize() {
        fileChooser = new FileChooser();
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Supported", "*.svg")
        );
        graphics = canvas.getGraphicsContext2D();
        canvas.widthProperty().bind(canvasWrapper.widthProperty());
        canvas.heightProperty().bind(canvasWrapper.heightProperty());
    }

    @FXML
    private void handleOpen(ActionEvent event) {
        file = fileChooser.showOpenDialog(Context.getPrimaryStage());
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
        rootShape.draw(graphics);
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
