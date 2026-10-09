namespace EmployeeApp;

public abstract class Employee : IComparable<Employee>
{
    private int id;
    private string name;
    private int age;
    private decimal salary;

    private static int totalCount;

    protected Employee(int id, string name, int age, decimal salary)
    {
        this.id = id;
        this.name = name;
        this.age = age;
        this.salary = salary;
        totalCount++;
    }

    public int Id
    {
        get => id;
        set => id = value;
    }

    public string Name
    {
        get => name;
        set => name = value;
    }

    public int Age
    {
        get => age;
        set => age = value;
    }

    public decimal Salary
    {
        get => salary;
        set => salary = value;
    }

    public static int TotalCount => totalCount;

    public int CompareTo(Employee? other)
    {
        if (other is null)
        {
            return 1;
        }

        return Id.CompareTo(other.Id);
    }

    public abstract string GetMessage();
}
