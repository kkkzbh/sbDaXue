

public record Student(string name);

public class Program
{
    public static void Main()
    {
        Student s = new("哈哈");
        Student s2 = s;
        Console.WriteLine(s2.name);
    }
}