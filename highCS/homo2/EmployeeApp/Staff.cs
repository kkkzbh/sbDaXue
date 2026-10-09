namespace EmployeeApp;

public class Staff : Employee
{
    private string post;

    public Staff(int id, string name, int age, decimal salary, string post)
        : base(id, name, age, salary)
    {
        this.post = post;
    }

    public string Post
    {
        get => post;
        set => post = value;
    }

    public override string GetMessage()
    {
        return $"普通员工  工号：{Id}  姓名：{Name}  年龄：{Age}  工资：{Salary:0.##}  岗位：{Post}";
    }
}
