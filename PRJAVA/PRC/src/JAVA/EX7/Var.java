package EX7;

public class Var    // 全局变量
{
    private int data = 0;   //默认为0的数据

    public void write(int val)
    {
        data = val;
    }

    public int read()
    {
        return data;
    }
}

