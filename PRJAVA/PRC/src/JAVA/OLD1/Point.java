package OLD1;


public class Point
{
    private int x;
    private int y;
    Point()
    {
        this(0,0);
    }
    Point(int X,int Y)
    {
        set(X,Y);
    }
    public void setx(int x)
    {
        this.x = x;
    }
    public void sety(int y)
    {
        this.y = y;
    }
    public void set(int x,int y)
    {
        setx(x);
        sety(y);
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
