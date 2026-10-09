package OLD1;


public class Rmatrix
{
    static Integer cnt = 1;
    public enum dirction
    {
        down(1),right(2);
        private final int v;
        dirction(int val)
        {
            v = val;
        }
        public int getVal()
        {
            return v;
        }
    }
    private static void fillRight(int[][] m,int x,int y,int n)
    {
        int i = x;
        int j = y;
        for(; j != y + n;++j) m[i][j] = cnt++;           //处理第一行
        for(++i,--j; i != x + n;++i) m[i][j] = cnt++;
        for(--i,--j;j != y - 1;--j) m[i][j] = cnt++;
        for(--i,++j; i != x;--i) m[i][j] = cnt++;
    }
    private static void fillDown(int[][] m,int x,int y,int n)
    {
        int i = x;
        int j = y;
        for(;i != x + n;++i) m[i][j] = cnt++;
        for(--i,++j; j != y + n;++j) m[i][j] = cnt++;
        for(--i,--j;i != x - 1;--i) m[i][j] = cnt++;
        for(++i,--j;j != y;--j) m[i][j] = cnt++;
    }
    private static int[][] for_solve(int n, dirction dir)
    {
        int[][] m = new int[n][n];
        int x = 0;
        int y = 0;
        cnt = 1;
        if(dir == dirction.down)
        {
            while(n > 1)
            {
                fillDown(m,x++,y++,n);
                n -= 2;
            }
            if(n == 1) m[x][y] = cnt;
            return m;
        }
        else
        {
            while(n > 1)
            {
                fillRight(m,x++,y++,n);
                n -= 2;
            }
            if(n == 1) m[x][y] = cnt;
        }
        return m;
    }
    public static int[][] solve(int n)
    {
        return for_solve(n, dirction.right);
    }
    public static int[][] solve(int n,int dir)
    {
        if(dir == 1) return for_solve(n,dirction.down);
        else return for_solve(n,dirction.right);
    }
    public static int[][] solve(int n,dirction d)
    {
        return for_solve(n,d);
    }
    public static void print(final int[][] m)
    {
        for(int i = 0; i != m.length;++i)
        {
            for(int j = 0; j != m[i].length;++j)
            {
                System.out.print(m[i][j] + " ");
            }
            System.out.print('\n');
        }
    }
}
