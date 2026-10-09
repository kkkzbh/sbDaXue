package JAVA.PetShop;

public abstract class Pet
{
    protected String name;
    protected int eatCount = 0;
    protected int sleepTime = 0;

    public abstract String toString();
    public abstract void eat();
    public abstract void sleep();
    Pet(String nm)
    {
        name = nm;
    }
    public String getName()
    {
        return name;
    }
    public int getEatCount()
    {
        return eatCount;
    }
    public int getSleepTime()
    {
        return sleepTime;
    }
}

class Cat extends Pet
{
    private int age = 0;
    private final String color;

    Cat(String nm,String color,int age)
    {
        super(nm);
        this.color = color;
        this.age = age;
    }
    public void eat()
    {
        ++eatCount;
    }
    public void eat(int count)
    {
        eatCount += count;
    }
    public void sleep()
    {
        sleepTime += 12;
    }
    public int getAge()
    {
        return age;
    }
    public String getColor()
    {
        return color;
    }
    public String toString()
    {
        return "猫猫" + name + age + "岁,是一只可爱的" + color + "色的猫猫";
    }
    public String characteristic()
    {
        return toString();
    }
    public String statistics()
    {
        return "猫猫" + name + "总计吃鱼" + eatCount + "两,总计睡眠" + sleepTime + "小时";
    }
}

class Dog extends Pet
{
    private int weigh = 0;
    private final String var;

    Dog(String name,String var,int weigh)
    {
        super(name);
        this.var = var;
        this.weigh = weigh;
    }
    public void eat()
    {
        ++eatCount;
    }
    public void eat(int count)
    {
        eatCount += count;
    }
    public void sleep()
    {
        sleepTime += 8;
    }
    public int getWeigh()
    {
        return weigh;
    }
    public String getVar()
    {
        return var;
    }
    public String toString()
    {
        return "狗狗" + name + "体重" + weigh + "公斤,是一只" + var +"狗";
    }
    public String characteristic()
    {
        return toString();
    }
    public String statistics()
    {
        return "狗狗" + name + "总计吃肉" + eatCount + "两,总计睡眠" + sleepTime + "小时";
    }
}
