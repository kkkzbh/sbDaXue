package JAVA;


class father
{
    public int i = 10;
    public int getI()
    {
        return i;
    }
}

class son extends father
{
}
class MAIN
{
    public static void main()
    {
        son s = new son();
        System.out.println(s.getI());
    }
}