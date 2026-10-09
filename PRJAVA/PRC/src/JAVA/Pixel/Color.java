package JAVA.Pixel;

public class Color
{
    private static final int ocpy = 0xff000000;
    private static final int red = 0x00ff0000;
    private static final int green = 0x0000ff00;
    private static final int blue = 0x000000ff;
    private int value;

    public Color(int rgb)
    {
        value = rgb;
        value |= ocpy;  //防左侧没填1
    }
    public Color(int r, int g, int b)
    {
        value = r << 16 | g << 8 | b;
    }
    public Color(Color color)
    {
        value = color.value;
    }
    public void reset(int r, int g, int b)
    {
        value = r << 16 | g << 8 | b | ocpy;
    }
    public void reset(int rgb)
    {
        value = rgb | ocpy;
    }
    public int getRGB()
    {
        return value & 0xff;
    }
    public int getRed()
    {
        return (value >> 16) & 0xff;
    }
    public int getGreen()
    {
        return (value >> 8) & 0xff;
    }
    public int getBlue()
    {
        return value & 0xff;
    }
    public String toString()
    {
        return "(" + getRed() + "," + getGreen() + "," + getBlue() + ")";
    }
}
