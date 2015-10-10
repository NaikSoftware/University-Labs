package ua.naiksoftware.g2dconversions;

import javafx.util.Callback;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import ua.naiksoftware.g2dconversions.model.Circle;
import ua.naiksoftware.g2dconversions.model.Line;
import ua.naiksoftware.g2dconversions.model.Rect;
import ua.naiksoftware.g2dconversions.model.Shape;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;

/**
 * Created by N on 06.10.2015.
 */
public class Parser extends DefaultHandler {

    public static void parse(File file, Callback<Shape, Void> callback) throws ParserConfigurationException, SAXException, IOException {
        SAXParserFactory saxFactory = SAXParserFactory.newInstance();
        SAXParser saxParser = saxFactory.newSAXParser();
        saxParser.parse(file, new Parser(callback));
    }

    private final Callback<Shape, Void> callback;
    private Shape root;

    private Parser(Callback<Shape, Void> callback) {
        this.callback = callback;
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attrs) throws SAXException {
        switch (qName) {
            case "svg":
                root = new Shape();
                break;
            case "line":
                root.addInner(new Line(
                        Double.parseDouble(attrs.getValue("x1")),
                        Double.parseDouble(attrs.getValue("y1")),
                        Double.parseDouble(attrs.getValue("x2")),
                        Double.parseDouble(attrs.getValue("y2"))
                ));
                break;
            case "rect":
                root.addInner(new Rect(
                        Double.parseDouble(attrs.getValue("x")),
                        Double.parseDouble(attrs.getValue("y")),
                        Double.parseDouble(attrs.getValue("width")),
                        Double.parseDouble(attrs.getValue("height"))
                ));
                break;
            case "circle":
                root.addInner(new Circle(
                        Double.parseDouble(attrs.getValue("cx")),
                        Double.parseDouble(attrs.getValue("cy")),
                        Double.parseDouble(attrs.getValue("r"))
                ));
                break;

        }
    }

    @Override
    public void endDocument() throws SAXException {
        callback.call(root);
    }
}
