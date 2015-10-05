package ua.naiksoftware.g2dconversions.controller;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.stage.FileChooser;
import ua.naiksoftware.g2dconversions.Context;

public class MainController {

    private FileChooser fileChooser;

    @FXML
    private void initialize() {
        fileChooser = new FileChooser();
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Supported", "*.svg")
        );
    }

    @FXML
    private void handleOpen(ActionEvent event) {
        fileChooser.showOpenDialog(Context.getPrimaryStage());
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
