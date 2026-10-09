package OLD1;

import java.util.Scanner;

public class _Guess
{
    public static void solve()
    {
        System.out.println("我想了一个数，你来猜猜看 --范围 (0 - 100)");
        int num = (int)(Math.random() * 100);
        int gues = -1;
        Scanner in = new Scanner(System.in);
        while(gues != num)
        {
            System.out.print("猜 :>");
            gues = in.nextInt();
            if(gues > num)
            {
                System.out.println("猜大了！");
            }
            else if(gues < num)
            {
                System.out.println("猜小了！");
            }
            else
            {
                System.out.println("恭喜猜对了！");
            }
        }
    }
}
