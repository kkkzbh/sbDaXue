package JAVA.Pixel;

public class Pixel extends Point
{
    private Color color;

    public Pixel(Point point, Color color)
    {
        super(point);
        this.color = new Color(color);
    }
    public Pixel(int x, int y, Color color)
    {
        super(x, y);
        this.color = new Color(color);
    }
    public Pixel(int x, int y, int color)
    {
        super(x, y);
        this.color = new Color(color);
    }
    public void resetPoint(int x, int y)
    {
        super.set(x, y);
    }
    public void resetRGB(int r, int g, int b)
    {
        color.reset(r, g, b);
    }
    public void resetRGB(int rgb)
    {
        color.reset(rgb);
    }
    public void reset(int x, int y, int color)
    {
        super.set(x, y);
        this.color.reset(color);
    }
    public Pixel(){}
    public String toString()
    {
        return "Pixel at " + super.toString() + " with color RGB" + color.toString();
    }
}

class Main
{
    public static void main(String[] args)
    {
        Pixel p = new Pixel(10,5,0xff123456);
        System.out.println(p);
        p.reset(0,0,0xff000000);
        System.out.println(p);
    }
}

