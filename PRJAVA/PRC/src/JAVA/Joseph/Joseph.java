package JAVA.Joseph;

public class Joseph
{
    private final int totalNum;
    private final int Count;
    private final int start;
    private Person head;

    public Joseph(int totalNum, int Count, int start)
    {
        this.totalNum = totalNum;
        this.Count = Count;
        this.start = start;
        CreateList();
    }
    private void CreateList()
    {
        int i = start;
        int cnt = totalNum;
        head = new Person(i++);
        Person it = head;
        while(--cnt != 0)
        {
            Person p = new Person(i++);
            it.together(p);;
            it = p;
        }
        it.together(head);
    }
    private Person select(Person it)
    {
        int cnt = Count;
        while(it.numberOff(--cnt))
        {
            it = it.next();
        }
        Person tmp = it;
        it = it.next();
        tmp.die();
        return it;
    }
    public void play()
    {
        int cnt = totalNum;
        Person it = head;
        while(cnt != 1)
        {
            it = select(it);
            --cnt;
        }
        head = it;
        System.out.println(head.getId() + "存活");
    }
}

class Demo
{
    public static void main(String[] args)
    {
        Joseph game = new Joseph(10,2,1);
        game.play();
    }
}
