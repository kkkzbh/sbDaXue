

package exprimentV.Stk;

import exprimentIV.Sorter.Cat;
import java.util.EmptyStackException;
import java.util.Random;

public class Stack<T> extends Vector<T>
{

    private int Cap = -1;

    public Stack(){}

    public Stack(int cap)
    {
        super(cap);
        Cap = cap;
    }

    public int size()
    {
        return super.size();
    }

    public boolean empty()
    {
        return super.empty();
    }

    public T push(T element)
    {
        if(Cap != -1 && size() == Cap)
            throw new FullStackException();
        push_back(element);
        return element;
    }

    public T pop()
    {
        if(Cap != -1 && size() == 0)
            throw new EmptyStackException();
        T val = (T) back();
        pop_back();
        return val;
    }

    public T peek()
    {
        if(Cap != -1 && size() == 0)
            throw new EmptyStackException();
        return (T)back();
    }
}



