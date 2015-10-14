package ua.naiksoftware.animandfractal.shapes;

import processing.core.PGraphics;
import ua.naiksoftware.animandfractal.Sketch;

import static processing.core.PApplet.*;

/**
 * Created by naik on 13.10.15.
 */
public class Wave {

    Sketch a;
    PGraphics g;
    float x, y, shape_width, speed;
    int shapes, y_shift;

    public Wave(Sketch a, int y, int color) {
        this.a = a;
        this.y = y;

        int factor = min(a.width, a.height);
        float amplitude = a.random(factor / 50, factor / 40);
        int step = (int) a.random(amplitude / 5, amplitude / 3);

        shape_width = TWO_PI / 0.1f * step;
        g = a.createGraphics((int)shape_width, (int)(amplitude * 2));
        g.beginDraw();
        g.beginShape();
        g.noStroke();
        g.background(255, 255, 0);
        g.fill(color);
        g.translate(0, amplitude);

        float x = 0;
        for (float i = 0; x <= shape_width + 1; i += 0.1) {
            g.vertex(x, sin(i) * amplitude);
            x += step;
        }
        g.vertex(x - step, amplitude);
        g.vertex(0, amplitude);
        g.endShape();

        shape_width--; // for overflow segments in draw method
        shapes = ceil((a.width + shape_width - 1) / shape_width) + 1;
        speed = a.random(0.5f, 3) * (shape_width % 5 > 2.5 ? 1 : -1);
        x = speed > 0 ? -shape_width : 0;
        y_shift = (int) (a.random(0, amplitude * 4));

        g.mask(createAlphaMask(g.width, g.height));
        cleanColor(g);
        g.endDraw();
    }

    public void display() {
        if (speed > 0) x = x < 0 ? x + speed : -shape_width;
        else x = x < -shape_width ? 0 : x + speed;
        for (int i = 0; i < shapes; i++) {
            a.image(g, x + i * shape_width, y + y_shift);
        }
    }

    PGraphics createAlphaMask(int w, int h) {
        PGraphics g = a.createGraphics(w, h);
        g.beginDraw();
        a.gradient(g, 0, 0, w, h, a.color(255, 255, 255), a.color(0, 0, 0), a.Y_AXIS);
        g.endDraw();
        return g;
    }

    void cleanColor(PGraphics g) {
        int w = g.width;
        int h = g.height;
        int color;
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                color = g.get(i, j);
                if (a.blue(color) < 170 && a.brightness(color) > 10) {
                    g.set(i, j, a.color(0, 0));
                }
            }
        }
    }
}
