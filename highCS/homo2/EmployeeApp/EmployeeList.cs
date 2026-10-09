using System.Text;

namespace EmployeeApp;

public class EmployeeList<T> where T : Employee
{
    private readonly List<T> employees = [];

    public int Count => employees.Count;

    public T this[int index] => employees[index];

    public T? this[string name]
    {
        get
        {
            return employees.FirstOrDefault(employee =>
                string.Equals(employee.Name, name, StringComparison.CurrentCultureIgnoreCase));
        }
    }

    public void Add(T employee)
    {
        employees.Add(employee);
    }

    public string Display()
    {
        StringBuilder builder = new();
        builder.AppendLine($"员工总数：{Employee.TotalCount}");

        if (employees.Count == 0)
        {
            builder.AppendLine("暂无员工信息。");
            return builder.ToString();
        }

        for (int i = 0; i < employees.Count; i++)
        {
            builder.AppendLine($"第 {i + 1} 条：{employees[i].GetMessage()}");
        }

        return builder.ToString();
    }

    public (int staffCount, decimal averageSalary) Average()
    {
        Staff[] staffs = employees.OfType<Staff>().ToArray();

        if (staffs.Length == 0)
        {
            return (0, 0);
        }

        return (staffs.Length, staffs.Average(staff => staff.Salary));
    }

    public void SortByIdAscending()
    {
        employees.Sort((left, right) => left.CompareTo(right));
    }

    public void SortByAgeDescending()
    {
        employees.Sort((left, right) => right.Age.CompareTo(left.Age));
    }
}
