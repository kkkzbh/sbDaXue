package EX8;

import java.awt.*;

public class KRect extends KShape
{
    private Vec vec = new Vec();

    KRect(){}

    @Override
    public void draw(Graphics g)
    {
        g.drawRect(vec.getStart().x,vec.getStart().y,vec.getDeltaX(),vec.getDeltaY());
    }

    KRect(int x1, int y1, int x2, int y2)
    {
        vec.setStart(x1,y1);
        vec.setEnd(x2,y2);
    }

    KRect(Point start, Point end)
    {
        vec.setStart(start);
        vec.setEnd(end);
    }

    public void setStart(int x,int y)
    {
        vec.setStart(x,y);
    }

    public void setStart(Point start)
    {
        vec.setStart(start);
    }

    public void setEnd(int x, int y)
    {
        vec.setEnd(x,y);
    }

    public void setEnd(Point end)
    {
        vec.setEnd(end);
    }

}
