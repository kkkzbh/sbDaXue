package OLD1;


public class Joseph
{
    private ArrayPerson ar;
    private int num;
    private int cnt;
    Joseph(int n,int ct)
    {
        ar = new ArrayPerson(n);
        num = n;
        cnt = ct;
        for(int i = 1; i <= n;++i)
        {
            ar.set(i,new Person(i));
        }
    }
    private int next(int index){ return ((index + cnt - 2) % num) + 1;}
    private void kill(int index)
    {
        ar.erase(index);
        --num;
    }
    public void solve()
    {
        int it = 1;
        while(num != 1)
        {
            it = next(it);
            kill(it);
        }
        System.out.print("最终胜利者的编号为 " + ar.at(1).get() + '\n');
    }
}
