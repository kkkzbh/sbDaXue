package EX8;

import java.awt.*;

public class Vec
{
    private Point start = new Point(0,0);
    private Point end = new Point(0,0);

    public Vec(){}

    public Vec(int x1, int y1, int x2, int y2)
    {
        start = new Point(x1, y1);
        end = new Point(x2, y2);
    }

    public Vec(Point start,Point end)
    {
        setStart(start);
        setEnd(end);
    }

    public Vec(Vec v)
    {
        start = new Point(v.start);
        end = new Point(v.end);
    }

    public void setStart(int x, int y)
    {
        start.setLocation(x,y);
    }

    public void setStart(Point p)
    {
        start = p;
    }

    public void setEnd(int x, int y)
    {
        end.setLocation(x,y);
    }

    public void setEnd(Point p)
    {
        end = p;
    }

    public Point getStart()
    {
        return new Point(start);
    }

    public Point getEnd()
    {
        return new Point(end);
    }

    public int getDeltaX()
    {
        return end.x - start.x;
    }

    public int getDeltaY()
    {
        return end.y - start.y;
    }

    public double getDistance()
    {
        double x1 = start.getX();
        double y1 = start.getY();
        double x2 = end.getX();
        double y2 = end.getY();
        return Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
    }

}
