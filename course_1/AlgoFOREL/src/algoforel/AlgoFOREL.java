package algoforel;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 *
 * @author Naik
 */
public class AlgoFOREL extends Application {

    @Override
    public void start(Stage primaryStage) {
        Parent parent = null;
        try {
            parent = FXMLLoader.load(getClass().getResource("main.fxml"));
            parent.getStylesheets().add("algoforel/chart.css");
        } catch (IOException ex) {
            Logger.getLogger(AlgoFOREL.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        Scene scene = new Scene(parent);

        primaryStage.setTitle("FOREL Algo by N.Soft");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }

}
