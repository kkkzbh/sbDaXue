package OLD1;

import OLD1.Person;

public class ArrayPerson
{
    private static final int SIZE = 100;
    private Person[] G;
    private int num = 0;

    ArrayPerson(){this(SIZE);}
    ArrayPerson(int n){G = new Person[n + 10]; num = n;}
    private void check(int index)
    {
        if(index <= 0 || index > num) throw new ArrayIndexOutOfBoundsException(index + "Segmentation fault!\n");
    }
    void erase(int index)
    {
        check(index);
        for(int i = index; i != num;++i) G[i] = G[i + 1];
        --num;
    }
    int getNum() { return num;}
    Person at(int index) { return G[index]; }
    void set(int index,Person p)
    {
        check(index);
        G[index] = p;
    }
}
