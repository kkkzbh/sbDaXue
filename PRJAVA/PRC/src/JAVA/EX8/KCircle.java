package EX8;

import java.awt.*;

public class KCircle extends KShape
{
    private Point center;
    private int r;

    public KCircle(){}

    @Override
    public void draw(Graphics g)
    {
        g.drawOval(center.x-r, center.y-r, 2*r, 2*r);
    }

    public KCircle(Point center)
    {
        setCenter(center);
    }

    public KCircle(int x,int y)
    {
        setCenter(x,y);
    }

    public KCircle(Point center, int r)
    {
        setCenter(center);
        setR(r);
    }

    public KCircle(int x, int y, int r)
    {
        setCenter(x,y);
        setR(r);
    }

    public void setCenter(Point center)
    {
        this.center = center;
    }

    public void setCenter(int x, int y)
    {
        center = new Point(x, y);
    }

    public void setR(int r)
    {
        this.r = r;
    }

    public Point getCenter()
    {
        return new Point(center);
    }

}