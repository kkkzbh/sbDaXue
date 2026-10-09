package exprimentV.Math;

public class Main
{
    public static void main(String[] args)
    {
        try{
            System.out.println(Math.fact(-1));
        }
        catch (NeqIntegerException e){
            System.out.printf("发生了错误：%s,错误数据:%d", e.getMessage(),e.getData());
        }
    }
}
