package exprimentIV.Sorter;

public class Cat implements Comparable<Cat>
{
    private String name;
    private int weigh = 0;
    private int heigh = 0;
    public Cat(){}
    public Cat(String name)
    {
        this.name = name;
    }
    public Cat(int wei,int hei)
    {
        setHeigh(hei);
        setWeigh(wei);
    }
    public void setWeigh(int wei)
    {
        weigh = wei;
    }
    public void setHeigh(int hei)
    {
        heigh = hei;
    }
    public void setName(String name)
    {
        this.name = name;
    }
    public int getWeigh()
    {
        return weigh;
    }
    public int getHeigh()
    {
        return heigh;
    }
    public String getName()
    {
        return name;
    }
    public int compareTo(Cat c1)
    {
        return weigh - c1.getWeigh();
    }
    public String toString()
    {
        return "[" + weigh + "," +  heigh + "]";
    }
}
