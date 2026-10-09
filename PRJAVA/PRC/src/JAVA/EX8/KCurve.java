package EX8;

import java.awt.*;
import java.util.ArrayList;

public class KCurve extends KShape
{
    ArrayList<Point> points = new ArrayList<>();

    @Override
    public void draw(Graphics g)
    {
        Point fp = null;
        for(Point p : points)
        {
            if(fp != null)
            {
                g.drawLine(fp.x, fp.y, p.x, p.y);
            }
                fp = p;
        }
    }

    public void addPoint(Point p)
    {
        points.add(p);
    }
}
