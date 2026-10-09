package OLD1;

public abstract class Animal
{
    protected abstract void run();
    public static void main(String[] args)
    {
        Tiger T = new Tiger();
        T.run();
        Tiger.A();
        T.bark();
    }
    public static void A()
    {
        System.out.print("1111");
    }
    private int i;
    private void bark()
    {
        System.out.println("bark0");
    }
}

class Tiger extends Animal
{
    public void run()
    {
        System.out.println("OLD1.Tiger is running!");
    }
    public static void A()
    {
        System.out.print("2222");
    }
    public void bark()
    {
        System.out.println("bark1");
    }
}

class Carp extends Animal
{
    public void run()
    {
        System.out.println("OLD1.Carp is running!");
    }
}

class Snake extends Animal
{
    public void run()
    {
        System.out.println("OLD1.Snake is running!");
    }
}