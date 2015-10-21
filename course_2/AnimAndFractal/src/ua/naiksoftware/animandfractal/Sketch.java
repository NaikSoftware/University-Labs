package ua.naiksoftware.animandfractal;

import processing.core.PApplet;
import processing.core.PGraphics;
import ua.naiksoftware.animandfractal.shapes.Fish;
import ua.naiksoftware.animandfractal.shapes.Star;
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
        //size(600, 300, P3D);
        size(1280, 768, P3D);
        fullScreen();
    }

    public int X_AXIS = 1, Y_AXIS = 2;

    int BG_START_COLOR = 0xFF7777aa, BG_END_COLOR = 0xFFccffcc;
    int SKY_BEGIN_COLOR = 0xFFddb600, SKY_END_COLOR = 0xFFff4c00;

    int WAVE_COUNT = 50;
    int STAR_COUNT = 50;
    int FISH_COUNT = 50;

    PGraphics background;
    Sun sun;
    Wave[] waves = new Wave[WAVE_COUNT];
    Star[] stars = new Star[STAR_COUNT];
    Fish[] fishs = new Fish[FISH_COUNT];

    long lastTime;
    int deltaTime;

    @Override
    public void setup() {
        int waterLine = height / 5;

        background = createGraphics(width, height);
        background.beginDraw();
        gradient(background, 0, waterLine, width, height, BG_START_COLOR, BG_END_COLOR, Y_AXIS);
        gradient(background, 0, 0, width, waterLine, SKY_BEGIN_COLOR, SKY_END_COLOR, Y_AXIS);
        background.endDraw();

        sun = new Sun(this);
        for (int i = 0; i < waves.length; i++)
            waves[i] = new Wave(this, waterLine, color(red(BG_START_COLOR), green(BG_START_COLOR),
                    random(blue(BG_START_COLOR) - 20, blue(BG_START_COLOR) + 70)));
        for (int i = 0; i < STAR_COUNT; i++) {
            stars[i] = new Star(this, waterLine, color(random(255), random(255), random(255), random(50, 200)));
        }
        for (int i = 0; i < FISH_COUNT; i++) {
            fishs[i] = new Fish(this, waterLine);
        }
        lastTime = millis();
    }

    @Override
    public void draw() {
        deltaTime = (int) (millis() - lastTime);
        image(background, 0, 0);
        for (Fish fish : fishs) fish.display(deltaTime);
        for (Wave wave : waves) wave.display(deltaTime);
        for (Star star : stars) star.display(deltaTime);
        sun.display();
        text(frameRate, 5, 40);
        lastTime = millis();
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
