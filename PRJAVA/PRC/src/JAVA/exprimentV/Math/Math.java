package exprimentV.Math;

public class Math
{
    public static long fact(int val)
    {
        if(val < 0)
            throw new NeqIntegerException("不能求负数的阶乘",val);
        long ret = 1;
        for(int i = 2; i <= val; i++)
        {
            ret *= i;
        }
        return ret;
    }
}
