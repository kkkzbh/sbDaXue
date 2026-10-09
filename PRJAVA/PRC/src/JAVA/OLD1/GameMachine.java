package OLD1;


import OLD1.Computer;

import java.util.Scanner;

public class GameMachine extends Computer
{
    private static final Scanner in = new Scanner(System.in);
    private static final GuessGame GUS = new GuessGame();
    private  enum select
    {
        nullptr(-1),EXIT(0),GUESS_GAME(1);
        int value;
        select(int num){ value = num;}
        int getValue(){ return value;}
        void set(int i) { value = i;}
        public static select get(int v)
        {
            for(select sc : values()) if(sc.getValue() == v) return sc;
            return nullptr;
        }
    }
    private static class GuessGame
    {
        private final int num = caculate();
        private int cnt = 0;
        private int v = -1;
        GuessGame(){}

        public void solve()
        {
            System.out.print("我想了一个数(0-100) 你来猜猜\n");
            while(v != num)
            {
                System.out.print("猜 :>");
                v = in.nextInt();
                if(v > num)
                {
                    System.out.print("猜大了！ 再猜猜\n");
                    ++cnt;
                }
                else if(v < num)
                {
                    System.out.print("猜小了！ 再猜猜\n");
                    ++cnt;
                }
                else
                {
                    System.out.print("恭喜猜对了！ 所用次数为 :" + cnt + "次\n");
                    System.out.print("欢迎下次再来！\n");
                }
            }
        }
    }
    private static void pmenu()
    {
        System.out.println("*************************************");
        System.out.println("********  1. GUESS_GAME  ************");
        System.out.println("********  0.  EXIT       ************");
        System.out.println("*************************************");
        System.out.println("欢迎来到菜单 请选择:>");
    }
    public static void menu()
    {
        pmenu();
        System.out.print("选择:>");
        select sec;
        do
        {
            sec = select.get(in.nextInt());
            switch (sec)
            {
                case EXIT:
                {
                    System.out.println("欢迎下次再来!");
                    break;
                }
                case GUESS_GAME:
                {
                    GUS.solve();
                    pmenu();
                    break;
                }
                case nullptr:
                {
                    System.out.println("输入有误 重新选择");
                    break;
                }
            }
        }while(sec != select.EXIT);
    }
}
