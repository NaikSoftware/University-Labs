package algoforel;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;
import javafx.scene.chart.XYChart.Data;

/**
 *
 * @author Naik
 */
public class Algo {

    private final ArrayList<Data<Double, Double>> points = new ArrayList<>();
    private double radius;

    public ArrayList<Data<Double, Double>> readFromFile(String path) throws FileNotFoundException, IOException {
        points.clear();
        BufferedReader reader = new BufferedReader(new FileReader(path));
        double x, y;
        for (String line : readLines(reader)) {
            String[] coords = line.split("\\s+");
            x = Double.parseDouble(coords[0]);
            y = Double.parseDouble(coords[1]);
            points.add(new Data(x, y));
        }
        return points;
    }

    public ArrayList<Data<Double, Double>> getClusters(double radius) {
        ArrayList<Data<Double, Double>> clusters = new ArrayList<>();
        ArrayList<Data<Double, Double>> neighbours;
        Random rnd = new Random();
        this.radius = radius;
        Data<Double, Double> current, center;
        while (clusterisationNeeded()) {
            current = points.get(rnd.nextInt(points.size()));
            neighbours = getNeighbourPoints(current);
            center = getCenterPoint(neighbours);
            while (center != current) {
                current = center;
                neighbours = getNeighbourPoints(current);
                center = getCenterPoint(neighbours);
            }
            Data cl = new Data(center.getXValue(), center.getYValue(), radius);
            clusters.add(cl);
            System.out.println("Neighbours: " + neighbours.size());
            System.out.println("Center point: " + center.getXValue() + ", " + center.getYValue());
            for (Data p : neighbours) {
                System.out.println("neighbour: " + p.getXValue() + ", " + p.getYValue());
                points.remove(p);
            }
        }
        return clusters;
    }

    private boolean clusterisationNeeded() {
        return points.size() > 0;
    }

    private ArrayList<Data<Double, Double>> getNeighbourPoints(Data<Double, Double> centerPoint) {
        ArrayList<Data<Double, Double>> neighbours = new ArrayList<>();
        for (Data<Double, Double> p : points) {
            if (Math.hypot(p.getXValue() - centerPoint.getXValue(),
                    p.getYValue() - centerPoint.getYValue()) <= radius) {
                neighbours.add(p);
            }
        }
        return neighbours;
    }

    private Data getCenterPoint(ArrayList<Data<Double, Double>> neighbours) {
        Data center = null;
        double sumX = 0, sumY = 0;
        for (Data<Double, Double> p : neighbours) {
            sumX += p.getXValue();
            sumY += p.getYValue();
        }
        double centerX = sumX / neighbours.size();
        double centerY = sumY / neighbours.size();
        double to_center = Double.MAX_VALUE, tmp;
        for (Data<Double, Double> p : points) {
            tmp = Math.hypot(p.getXValue() - centerX, p.getYValue() - centerY);
            if (tmp < to_center) {
                to_center = tmp;
                center = p;
            }
        }
        return center;
    }

    private static Iterable<String> readLines(BufferedReader reader) throws IOException {
        ArrayList<String> arr = new ArrayList<>();
        String line;
        while ((line = reader.readLine()) != null) {
            line = line.trim();
            if (!line.isEmpty()) {
                arr.add(line.replace(",", "."));
            }
        }
        return arr;
    }

}
