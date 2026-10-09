package OLD1;


public class Ta
{
    public static void solve(int n)
    {
        for(int i = 1; i <= n;++i)  //行数
        {
            for(int j = 1; j <= n - i;++j) //打印前缀空白
            {
                System.out.print("   ");
            }
            for(int j = 1; j <= i;++j)  //打印左半部分
            {
                System.out.print(" " + j + " ");
            }
            for(int j = i - 1; j >= 1;--j)
            {
                System.out.print(" " + j + " ");
            }
            System.out.print('\n');
        }
    }
}
