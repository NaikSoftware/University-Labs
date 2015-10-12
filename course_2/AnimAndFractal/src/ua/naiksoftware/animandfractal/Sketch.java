package ua.naiksoftware.animandfractal;

import processing.core.PApplet;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.DoubleStream;
import java.util.stream.Stream;

/**
 * Created by naik on 12.10.15.
 */
public class Sketch extends PApplet {

    @Override
    public void settings() {
        size(800, 600);
    }

    int X_AXIS = 1, Y_AXIS = 2;

    @Override
    public void draw() {
        clear();
        gradient(0, 0, width, height, color(0xFF7777aa), color(0xFFccffcc), Y_AXIS);
        float x1 = map(mouseX, 0, width, width / 2 - 100, width / 2 + 100);
        ellipse(x1, 75, 50, 50);
    }

    void gradient(int x, int y, float w, float h, int color1, int color2, int axis) {
        if (axis == Y_AXIS) {  // Top to bottom gradient
            for (int i = y; i <= y + h; i++) {
                float inter = map(i, y, y + h, 0, 1);
                int c = lerpColor(color1, color2, inter);
                stroke(c);
                line(x, i, x + w, i);
            }
        } else if (axis == X_AXIS) {  // Left to right gradient
            for (int i = x; i <= x + w; i++) {
                float inter = map(i, x, x + w, 0, 1);
                int c = lerpColor(color1, color2, inter);
                stroke(c);
                line(i, y, i, y + h);
            }
        }
    }

    void log_color(int argb) {
        System.out.println(Arrays.asList(alpha(argb), red(argb), green(argb), blue(argb)).stream()
                .map(Object::toString).collect(Collectors.joining("\t")));
    }
}
