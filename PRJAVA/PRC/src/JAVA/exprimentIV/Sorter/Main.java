package exprimentIV.Sorter;

import java.util.Arrays;

public class Main
{
    public static void main(String[] args)
    {
        Integer[] data = {11, 3, 25, 8, 9, 36, 13, 29, 10, 50};
        Sorter<Integer> cs = new Sorter<Integer>(new IntegerComparator());
        cs.sort(data);
        for (Integer i : data) System.out.println(i);
        Cat[] cats = new Cat[10];
        cats[0] = new Cat(11, 50);
        cats[1] = new Cat(3, 10);
        cats[2] = new Cat(25, 29);
        cats[3] = new Cat(8, 13);
        cats[4] = new Cat(9, 36);
        cats[5] = new Cat(36, 9);
        cats[6] = new Cat(13, 8);
        cats[7] = new Cat(29, 25);
        cats[8] = new Cat(10, 3);
        cats[9] = new Cat(50, 11);
        Sorter<Cat> cs2 = new Sorter<Cat>(new CatHeightComparator());
        cs2.sort(cats);
        for (Cat c : cats) System.out.println(c);

    }
}
