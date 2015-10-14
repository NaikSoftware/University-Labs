package ua.naiksoftware.animandfractal.shapes;

import processing.core.PGraphics;
import processing.core.PVector;
import ua.naiksoftware.animandfractal.Sketch;

import static processing.core.PApplet.*;

/**
 * Created by naik on 14.10.15.
 */
public class Star {

    Sketch a;
    PGraphics g;
    float x, y;
    float dx, dy;
    int minY, maxY, minX, maxX;

    public Star(Sketch a, int waterLine, int color) {
        this.a = a;
        int factor = min(a.width, a.height);
        int height = (int) (a.random(factor / 20, factor / 6) * 1.5);
        int width = height * 2;
        minX = 0;
        maxX = a.width - width;
        minY = waterLine + (a.height - waterLine) / 2;
        maxY = a.height - height;
        x = a.random(minX, maxX);
        y = a.random(minY, maxY);
        float z = a.random(-400, -100);
        dx = a.random(-1.5f, 1.5f);
        dy = a.random(-0.4f, 0.4f);

        g = a.createGraphics(width, height, P3D);
        g.beginDraw();
        g.noStroke();
        g.fill(color);
        g.pushMatrix();
        g.translate(0, 0, -height);
        g.rotateX(radians(45));
        g.beginShape();
        generateKochSnowflake(width / 2, height / 2, height*0.7, 3, (int) a.random(2, 5));
        g.endShape();
        g.popMatrix();
        g.endDraw();
    }

    void generateKochSegment(int x1, int y1, int x2, int y2, int n) {
        if (n == 0) g.vertex(x1, y1);
        else {
            int x3 = (2 * x1 + x2) / 3;
            int y3 = (2 * y1 + y2) / 3;

            int x4 = (int) ((x1 + x2) / 2 - (y1 - y2) * Math.sqrt(3) / 6);
            int y4 = (int) ((y1 + y2) / 2 + (x1 - x2) * Math.sqrt(3) / 6);

            int x5 = (x1 + 2 * x2) / 3;
            int y5 = (y1 + 2 * y2) / 3;

            //g.triangle(x3, y3, x4, y4, x5, y5); // fill segment

            generateKochSegment(x1, y1, x3, y3, n - 1);
            generateKochSegment(x3, y3, x4, y4, n - 1);
            generateKochSegment(x4, y4, x5, y5, n - 1);
            generateKochSegment(x5, y5, x2, y2, n - 1);
        }
    }

    void generateKochSnowflake(int xc, int yc, double dim, int sides, int n) {
        int[] sideX = new int[sides];
        int[] sideY = new int[sides];
        for (int i = 0; i < sides; ++i) {
            sideX[i] = (int) (xc + dim * cos(TWO_PI / sides * i));
            sideY[i] = (int) (yc - dim * sin(TWO_PI / sides * i));
        }
        for (int i = 0; i < sides; ++i) {
            int from = (i + 1) % sides;
            generateKochSegment(sideX[from], sideY[from], sideX[i], sideY[i], n);
        }
    }

    public void display() {
        if (x < minX || x > maxX) dx *= -1;
        if (y < minY || y > maxY) dy *= -1;
        x += dx;
        y += dy;
        a.image(g, x, y);
    }
}
