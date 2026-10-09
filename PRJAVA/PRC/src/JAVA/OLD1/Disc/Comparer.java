package OLD1.Disc;

public abstract class Comparer
{
    public abstract int compare(Object a,Object b);
    public abstract boolean isRight(Object a);
}

class IntegerComparer extends Comparer
{
    public int compare(Object Ia,Object Ib)
    {
        if(!(Ia instanceof Integer a) || !(Ib instanceof Integer b)) throw new IllegalArgumentException();
        return -a.compareTo(b);
    }
    public boolean isRight(Object[] arr)
    {
        return isRight(arr[0]);
    }
    public boolean isRight(Object a)
    {
        return a instanceof Integer;
    }
}

class CatHeightComparer extends Comparer
{
    public int compare(Object Cat1,Object Cat2)
    {
        if(!(Cat1 instanceof Cat a) || !(Cat2 instanceof Cat b)) throw new IllegalArgumentException();
        return -Integer.compare(a.getHeigh(), b.getHeigh());
    }
    public boolean isRight(Object[] arr)
    {
        return isRight(arr[0]);
    }
    public boolean isRight(Object a)
    {
        return a instanceof Cat;
    }
}