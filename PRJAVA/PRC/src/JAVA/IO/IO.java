package IO;


interface In
{
    public abstract char readChar();
}

interface Out
{
    public abstract void putChar();
}

class readFromKeyBoard implements In
{
    public char readChar()
    {
        //实现输入流的读取功能...
        char c = 0;
        return c;
    }
}

class printToPrinter implements Out
{
    public void putChar()
    {
        //实现输出流的输出功能...
        System.out.print("0");
    }
}

public class IO
{
    public static void main(String[] args)
    {
        final int EOF = 0;
        In in = new readFromKeyBoard();
        Out out = new printToPrinter();
        char c;
        while((c = in.readChar()) != EOF) out.putChar();
    }
}
