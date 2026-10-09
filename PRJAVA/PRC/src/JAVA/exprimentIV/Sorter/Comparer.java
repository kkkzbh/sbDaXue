package exprimentIV.Sorter;


import java.util.Comparator;

public interface Comparer
{
    public abstract int compare(Object a, Object b);
}

class IntegerComparer implements Comparer
{
    public int compare(Object Ia,Object Ib)
    {
        return -(((Integer) Ia).compareTo((Integer) Ib));
    }
}

class CatHeightComparer implements Comparer
{
    public int compare(Object a,Object b)
    {
        return -(Integer.compare(((Cat)a).getHeigh(), ((Cat)b).getHeigh()));
    }
}

class IntegerComparator implements Comparator<Integer>
{
    public int compare(Integer a, Integer b)
    {
        return -(a.compareTo(b));
    }
}

class CatHeightComparator implements Comparator<Cat>
{
    public int compare(Cat a, Cat b)
    {
        return -(a.getHeigh() - b.getHeigh());
    }
}