package exprimentV.Stk;

import java.util.NoSuchElementException;

public class Vector<T>
{
    private Object[] a = new Object[1];
    private int sz = 0;
    private int cap = 1;

    public Vector(){}
    public Vector(int cap)
    {
        this.cap = cap;
        a = new Object[cap];
    }

    public void push_back(Object val)
    {
        if(sz == cap)
            realloc();
        a[sz++] = val;
    }

    public void pop_back()
    {
        if(sz == 0)
            throw new NoSuchElementException("Vector is empty");
        --sz;
    }

    Object at(int index)
    {
        if(index < 0 || index >= sz)
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + sz);
        return a[index];
    }

    Object front()
    {
        if(sz == 0)
            throw new NoSuchElementException("Vector is empty");
        return a[0];
    }

    Object back()
    {
        if(sz == 0)
            throw new NoSuchElementException("Vector is empty");
        return a[sz - 1];
    }

    public int size()
    {
        return sz;
    }

    public int capacity()
    {
        return cap;
    }

    public boolean empty()
    {
        return sz == 0;
    }

    private void realloc()
    {
        Object[] temp = new Object[cap *= 2];
        System.arraycopy(a, 0, temp, 0, sz);
        a = temp;
    }
}
