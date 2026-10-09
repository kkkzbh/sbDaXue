package JAVA.T13;

import java.awt.*;
import java.util.ArrayList;

public class MyCurv extends MyShape{
    private ArrayList<Point> points = new ArrayList<>();
    @Override
    public void draw(Graphics g) {
        Point p=points.get(0);
        for(int i=1;i<points.size();i++){
            Point p1=points.get(i);
            g.drawLine(p1.x,p1.y,p.x,p.y);
            p=p1;
        }
    }

    public void addPoint(Point point) {
        points.add(point);
    }
}
