package JAVA.Pixel;

public class Point
{
    private int x;
    private int y;
    public Point()
    {
        this(0,0);
    }
    public Point(int X,int Y)
    {
        set(X,Y);
    }
    public Point(Point p)
    {
        set(p.x,p.y);
    }
    public void setX(int x)
    {
        this.x = x;
    }
    public void setY(int y)
    {
        this.y = y;
    }
    public void set(int x,int y)
    {
        setX(x);
        setY(y);
    }
    public int getx()
    {
        return x;
    }
    public int gety()
    {
        return y;
    }
    public String toString()
    {
        return "(" + x + ',' + y + ")";
    }
}
