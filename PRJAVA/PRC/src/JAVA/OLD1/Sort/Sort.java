package OLD1.Sort;

import java.util.Arrays;
import java.util.Comparator;

/* *********************************************** /*
    Comparable 默认比较年龄
    另外实现两个Comparator比较体重和名字
/* *********************************************** */


class Person implements Comparable<Person>
{
    private String name;
    private int age;
    private int heigh;
    public Person(){}
    public Person(String name, int age,int heigh)
    {
        this.name = name;
        this.age = age;
        this.heigh = heigh;
    }

    public String getName()
    {
        return name;
    }
    public int getAge()
    {
        return age;
    }
    public int getHeigh()
    {
        return heigh;
    }

    @Override
    public int compareTo(Person p)
    {
        return this.getAge() - p.getAge();
    }

    @Override
    public String toString()
    {
        return this.name + "年龄: " + this.age + " 体重: " + this.heigh;
    }
}

class PersonNameComparator implements Comparator<Person>
{
    public int compare(Person e1,Person e2)
    {
        return e1.getName().compareTo(e2.getName());
    }
}

class PersonHeightComparator implements Comparator<Person>
{
    public int compare(Person e1, Person e2)
    {
        return e1.getHeigh() - e2.getHeigh();
    }
}

public class Sort
{
    public static void main(String[] args)
    {
        Person[] a = {new Person("A",5,18), new Person("E",95,74),new Person("D",45,1),
                new Person("BBB",12,20), new Person("XC",23,23)};
        Arrays.sort(a);
        for(Person i : a)
        {
            System.out.println(i);
        }
        System.out.println();
        Arrays.sort(a,new PersonNameComparator());
        for(Person i : a)
        {
            System.out.println(i);
        }
        System.out.println();
        Arrays.sort(a,new PersonHeightComparator());
        for(Person i : a)
        {
            System.out.println(i);
        }
        System.out.println();
    }
}
