package ua.naiksoftware.animandfractal.shapes;

import processing.core.PImage;
import ua.naiksoftware.animandfractal.Sketch;

import static processing.core.PApplet.*;

/**
 * Created by naik on 13.10.15.
 */
public class Sun {

    int size;
    int minx;

    Sketch a;
    PImage image;

    public Sun(Sketch a) {
        this.a = a;
        size = min(a.width, a.height) / 10;
        minx = a.width - size * 3;
        image = a.loadImage("sun.png");
        image.resize(size, size);
    }

    public void display() {
        float x = map(a.mouseX, 0, a.width, minx, a.width - size);
        a.image(image, x, 20);
    }
}
