package exprimentV.Math;

public class NeqIntegerException extends RuntimeException
{
    int val;
    public NeqIntegerException()
    {
        super();
    }
    public NeqIntegerException(String s)
    {
        super(s);
    }
    public NeqIntegerException(String s,int a)
    {
        super(s);
        val = a;
    }
    public int getData()
    {
        return val;
    }
}
