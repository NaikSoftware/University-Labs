package ua.naiksoftware.animandfractal.shapes;

import processing.core.PGraphics;
import processing.core.PImage;
import ua.naiksoftware.animandfractal.Sketch;

import static processing.core.PApplet.min;
import static processing.core.PApplet.println;

/**
 * Created by naik on 14.10.15.
 */
public class Fish {

    Sketch a;
    PGraphics g;
    float x, y, dx, dy;
    int maxX, waterLine;
    int bound = 400;

    public Fish(Sketch a, int waterLine) {
        this.a = a;
        this.waterLine = waterLine;
        int factor = min(a.width, a.height);
        int width = (int) a.random(factor / 20, factor / 17);
        String file = "caras" + (int) (a.random(3)) + ".png";
        println(file);
        PImage image = a.loadImage(file);
        image.resize(width, (image.height / image.width) * width);
        g = a.createGraphics(image.width, image.height);
        g.beginDraw();
        g.image(image, 0, 0);
        g.endDraw();
        maxX = a.width + bound;
        genNew(1);
    }

    void genNew(int direction) {
        float newDirect = a.random(-1, 1);
        if (newDirect > 0) {
            x = a.random(-bound, 0);
            dx = a.random(1, 3);
        } else {
            x = a.random(maxX - bound, maxX);
            dx = a.random(-3, -1);
        }
        y = a.random(waterLine, waterLine + (a.height - waterLine) / 2);
        dy = a.random(-0.01f, 0.01f);

        if (newDirect > 0 && direction < 0 || newDirect < 0 && direction > 0) {
            g.scale(-1, 1); // flip horizontally
        }
    }

    public void display() {
        if (x > maxX || x < -bound) genNew(1);
        x += dx;
        y += dy;
        a.image(g, x, y);
    }
}
