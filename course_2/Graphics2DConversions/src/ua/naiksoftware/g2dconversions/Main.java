package ua.naiksoftware.g2dconversions;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.util.ResourceBundle;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        System.setProperty("prism.lcdtext", "false"); // Improve font rendering
        Context.init(ResourceBundle.getBundle("i18n.Language"), primaryStage);
        primaryStage.setTitle("G2D Conversions");
        Context.loadToStage("Main").show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
