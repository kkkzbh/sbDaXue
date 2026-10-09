package OLD1;

import java.util.Scanner;

public class _Joseph
{
    public static void solve()
    {
        Scanner in = new Scanner(System.in);
        int N,M;
        N = in.nextInt();
        M = in.nextInt();
        int[] a = new int[N];
        int count = 1;
        int it = 0;
        while(count != N)
        {
            for(int i = 1; i < M;++i)
            {
                while(a[it++] == 1) it %= N;
                it %= N;
            }
            while(a[it] == 1)
            {
                ++it;
                it %= N;
            }
            a[it++] = 1;
            it %= N;
            ++count;
        }
        int id = 0;
        for(int i = 0 ; i < N;++i) {
            if (a[i] == 0) id = i;
        }
        System.out.print(id + 1);
    }

}
