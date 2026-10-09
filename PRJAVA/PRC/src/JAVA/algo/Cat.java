package algo;


public class Cat implements Comparable<Cat>
{
    private String name;
    private int height;
    private int weight;

    public Cat(){}

    public Cat(String name)
    {
        this.name = name;
    }

    public Cat(String name, int height)
    {
        this.name = name;
        this.height = height;
    }

    public Cat(String name, int height, int weight)
    {
        this.name = name;
        this.height = height;
        this.weight = weight;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public void setHeight(int height)
    {
        this.height = height;
    }

    public void setWeigh(int weight)
    {
        this.weight = weight;
    }

    public int compareTo(Cat a)
    {
        return this.height - a.height;
    }

    public String toString()
    {
        return "[姓名:" + this.name + ",身高:" + this.height + ",体重: " + this.weight + "]";
    }
}
