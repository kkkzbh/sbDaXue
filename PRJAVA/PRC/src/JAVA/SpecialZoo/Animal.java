package JAVA.SpecialZoo;

public abstract class Animal
{
    public abstract void feed();
    public abstract void thank();
    public abstract void play();
}

class Dog extends Animal
{

    public void feed(){ System.out.println("喂肉骨头"); }
    public void thank(){ System.out.println("汪汪汪"); }
    public void play(){ System.out.println("玩儿飞盘"); }
}

class Cat extends Animal
{
    public void feed(){ System.out.println("喂小飞鱼"); }
    public void thank(){ System.out.println("米易嗷呜"); }
    public void play(){ System.out.println("捉蝴蝶"); }
}

class Chick extends Animal
{
    public void feed(){ System.out.println("喂小虫子"); }
    public void thank(){ System.out.println("叽叽叽"); }
    public void play(){ System.out.println("走在走去翻翻找找"); }
}

class Main
{
    public static void main(String[] args)
    {
        Animal dog = new Dog();
        Animal cat = new Cat();
        Animal chick = new Chick();
        dog.feed();
        cat.feed();
        chick.feed();
        chick.thank();
    }
}
