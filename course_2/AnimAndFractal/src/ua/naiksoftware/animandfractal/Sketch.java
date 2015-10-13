package ua.naiksoftware.animandfractal;

import processing.core.PApplet;
import processing.core.PGraphics;
import ua.naiksoftware.animandfractal.shapes.Sun;
import ua.naiksoftware.animandfractal.shapes.Wave;

import java.util.Arrays;
import java.util.stream.Collectors;

/**
 * Created by naik on 12.10.15.
 */
public class Sketch extends PApplet {

    @Override
    public void settings() {
        //size(600, 300);
        //size(1280, 768);
        fullScreen();
    }

    public int X_AXIS = 1, Y_AXIS = 2;

    int BG_START_COLOR = 0xFF7777aa, BG_END_COLOR = 0xFFccffcc;
    int SKY_BEGIN_COLOR = 0xFFddb600, SKY_END_COLOR = 0xFFff4c00;

    int WAVE_COUNT = 10;

    int WATER_LINE;
    Wave[] waves = new Wave[WAVE_COUNT];
    Sun sun;

    @Override
    public void setup() {
        smooth();
        WATER_LINE = height / 5;
        sun = new Sun(this);
        for (int i = 0; i < waves.length; i++)
            waves[i] = new Wave(this,
                    color(red(BG_START_COLOR), green(BG_START_COLOR),
                            random(blue(BG_START_COLOR) - 20, blue(BG_START_COLOR) + 70)));
    }

    @Override
    public void draw() {
        clear();
        gradient(g, 0, WATER_LINE, width, height, BG_START_COLOR, BG_END_COLOR, Y_AXIS);
        gradient(g, 0, 0, width, WATER_LINE, SKY_BEGIN_COLOR, SKY_END_COLOR, Y_AXIS);
        for (Wave wave : waves) wave.display(WATER_LINE);
        sun.display();
    }

    public void gradient(PGraphics g, int x, int y, float w, float h, int color1, int color2, int axis) {
        if (axis == Y_AXIS) {  // Top to bottom gradient
            for (int i = y; i <= y + h; i++) {
                float inter = map(i, y, y + h, 0, 1);
                int c = lerpColor(color1, color2, inter);
                g.stroke(c);
                g.line(x, i, x + w, i);
            }
        } else if (axis == X_AXIS) {  // Left to right gradient
            for (int i = x; i <= x + w; i++) {
                float inter = map(i, x, x + w, 0, 1);
                int c = lerpColor(color1, color2, inter);
                g.stroke(c);
                g.line(i, y, i, y + h);
            }
        }
    }

    public void log_color(int argb) {
        System.out.println(Arrays.asList(alpha(argb), red(argb), green(argb), blue(argb)).stream()
                .map(Object::toString).collect(Collectors.joining("\t")));
    }
}
