package OLD1.Disc;

public class Cat
{
    private int weigh = 0;
    private int heigh = 0;
    public Cat(){}
    public Cat(int wei,int hei)
    {
        setHeigh(hei);
        setWeigh(wei);
    }
    public void setWeigh(int wei){ weigh = wei;}
    public void setHeigh(int hei){ heigh = hei;}
    public int getWeigh(){ return weigh;}
    public int getHeigh(){ return heigh;}
    public String toString()
    {
        return "[" + weigh + "," + heigh + "]";
    }
}
