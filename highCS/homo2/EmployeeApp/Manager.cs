namespace EmployeeApp;

public class Manager : Employee
{
    private string department;

    public Manager(int id, string name, int age, decimal salary, string department)
        : base(id, name, age, salary)
    {
        this.department = department;
    }

    public string Department
    {
        get => department;
        set => department = value;
    }

    public override string GetMessage()
    {
        return $"管理人员  工号：{Id}  姓名：{Name}  年龄：{Age}  工资：{Salary:0.##}  部门：{Department}";
    }
}
