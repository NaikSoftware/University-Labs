package algoforel;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.chart.Axis;
import javafx.scene.chart.BubbleChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.Tooltip;
import javafx.stage.FileChooser;

/**
 * FXML Controller class
 *
 * @author Naik
 */
public class MainController implements Initializable {

    @FXML
    private Button btnOpenData;
    @FXML
    private Label labelFile;
    @FXML
    private Button btnRun;
    @FXML
    private TextArea textAreaResult;
    @FXML
    private BubbleChart<Double, Double> bubbleChart;
    @FXML
    private TextField clusterSize;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }

    @FXML
    private void onOpenData(ActionEvent event) {
        FileChooser chooser = new FileChooser();
        chooser.setTitle("Select text file with x, y lines");
        chooser.setInitialDirectory(new File(System.getProperty("user.home")));
        File file = chooser.showOpenDialog(((Node) event.getTarget()).getScene().getWindow());
        if (file != null && file.exists()) {
            labelFile.setText(file.getAbsolutePath());
        }
    }

    @FXML
    private void onRun(ActionEvent event) {
        bubbleChart.getData().clear();
        ArrayList<XYChart.Data<Double, Double>> points = null;
        Algo algo = new Algo();
        try {
            points = algo.readFromFile(labelFile.getText());
        } catch (IOException ex) {
            Logger.getLogger(MainController.class.getName()).log(Level.SEVERE, null, ex);
        }
        XYChart.Series series1 = new XYChart.Series();
        series1.setName("2D Points");
        for (XYChart.Data p : points) {
            series1.getData().add(p);
        }
        bubbleChart.getData().add(series1);
        ObservableList<XYChart.Data> dataList = series1.getData();
        for (XYChart.Data data : dataList) {
            Node node = data.getNode();
            Tooltip tooltip = new Tooltip('(' + data.getXValue().toString() + " ; " + data.getYValue().toString() + ')');
            Tooltip.install(node, tooltip);
        }

        double cluster_size = 25;
        try {
            cluster_size = Double.parseDouble(clusterSize.getText().replace(",", ".")) / 2d;
        } catch (NumberFormatException ex) {
            Logger.getLogger(MainController.class.getName()).log(Level.SEVERE, null, ex);
        }
        ArrayList<XYChart.Data<Double, Double>> clusters = algo.getClusters(cluster_size);
        XYChart.Series series2 = new XYChart.Series();
        series2.setName("Clusters");
        for (XYChart.Data cl : clusters) {
            series2.getData().add(cl);
        }
        bubbleChart.getData().add(series2);
        StringBuilder sb = new StringBuilder("Clusters:\n-------\n\n");
        dataList = series2.getData();
        for (XYChart.Data data : dataList) {
            sb.append("Cluster ").append(data.getXValue()).append(", ")
                    .append(data.getYValue()).append("\n");
            Node node = data.getNode();
            Tooltip tooltip = new Tooltip("Cluster "
                    + '(' + data.getXValue().toString() + " ; " + data.getYValue().toString() + ')');
            Tooltip.install(node, tooltip);
        }
        textAreaResult.setText(sb.toString());
    }

}
