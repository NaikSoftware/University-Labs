package ua.naiksoftware.animandfractal.shapes;

import processing.core.PGraphics;
import processing.core.PImage;
import ua.naiksoftware.animandfractal.Sketch;

import static processing.core.PApplet.*;

/**
 * Created by naik on 14.10.15.
 */
public class Fish {

    Sketch a;
    PGraphics g;
    PImage image;
    float x, y, dx, dy;
    int maxX, minY, waterLine;
    int bound;

    public Fish(Sketch a, int waterLine) {
        this.a = a;
        this.waterLine = waterLine;
        int factor = min(a.width, a.height);
        int width = (int) a.random(factor / 20, factor / 13);
        image = a.loadImage("caras" + (int) (a.random(3)) + ".png");
        image.resize(width, (image.height / image.width) * width);
        g = a.createGraphics(image.width, image.height);
        bound = a.width / 2;
        maxX = a.width + bound;
        minY = waterLine + factor / 9;
        toNewPlace();
    }

    void toNewPlace() {
        g.beginDraw();
        g.clear();

        float newDirect = a.random(-1, 1);
        if (newDirect > 0) {
            x = a.random(-bound, 0);
            dx = a.random(0.05f, 0.08f);
            g.scale(1, 1);
            g.image(image, 0, 0);
        } else {
            x = a.random(maxX - bound, maxX);
            dx = a.random(-0.08f, -0.05f);
            g.scale(-1, 1);
            g.image(image, -image.width, 0);
        }
        y = a.random(minY, waterLine + (a.height - waterLine) / 2);
        dy = a.random(-0.002f, 0.002f);

        g.endDraw();
    }

    public void display(int deltaTime) {
        if (x > maxX || x < -bound) toNewPlace();
        x += dx * deltaTime;
        y += dy * deltaTime;
        a.image(g, x, y);
    }
}
