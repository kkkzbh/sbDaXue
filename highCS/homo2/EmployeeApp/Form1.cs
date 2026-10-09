namespace EmployeeApp;

public partial class Form1 : Form
{
    private readonly EmployeeList<Employee> employees = new();

    public Form1()
    {
        InitializeComponent();
    }

    private void btnAddStaff_Click(object sender, EventArgs e)
    {
        if (!TryReadCommonFields(out int id, out string name, out int age, out decimal salary))
        {
            return;
        }

        string post = txtPost.Text.Trim();
        if (string.IsNullOrWhiteSpace(post))
        {
            ShowInputError("请输入岗位。");
            txtPost.Focus();
            return;
        }

        employees.Add(new Staff(id, name, age, salary, post));
        txtResult.Text = $"已添加普通员工：{name}";
        ClearInputs();
    }

    private void btnAddManager_Click(object sender, EventArgs e)
    {
        if (!TryReadCommonFields(out int id, out string name, out int age, out decimal salary))
        {
            return;
        }

        string department = txtDepartment.Text.Trim();
        if (string.IsNullOrWhiteSpace(department))
        {
            ShowInputError("请输入部门。");
            txtDepartment.Focus();
            return;
        }

        employees.Add(new Manager(id, name, age, salary, department));
        txtResult.Text = $"已添加管理人员：{name}";
        ClearInputs();
    }

    private void btnDisplayAll_Click(object sender, EventArgs e)
    {
        txtResult.Text = employees.Display();
    }

    private void btnAverage_Click(object sender, EventArgs e)
    {
        (int staffCount, decimal averageSalary) = employees.Average();
        txtResult.Text = $"普通员工总数：{staffCount}{Environment.NewLine}普通员工平均工资：{averageSalary:0.00}";
    }

    private void btnSortById_Click(object sender, EventArgs e)
    {
        employees.SortByIdAscending();
        txtResult.Text = "已按工号升序排序。" + Environment.NewLine + employees.Display();
    }

    private void btnSortByAge_Click(object sender, EventArgs e)
    {
        employees.SortByAgeDescending();
        txtResult.Text = "已按年龄降序排序。" + Environment.NewLine + employees.Display();
    }

    private void btnFindByName_Click(object sender, EventArgs e)
    {
        string name = txtName.Text.Trim();
        if (string.IsNullOrWhiteSpace(name))
        {
            ShowInputError("请输入要查找的姓名。");
            txtName.Focus();
            return;
        }

        Employee? employee = employees[name];
        txtResult.Text = employee is null ? $"未找到姓名为“{name}”的员工。" : employee.GetMessage();
    }

    private void btnShowByIndex_Click(object sender, EventArgs e)
    {
        if (!int.TryParse(txtIndex.Text.Trim(), out int displayIndex))
        {
            ShowInputError("请输入要显示的序号。");
            txtIndex.Focus();
            return;
        }

        int index = displayIndex - 1;
        if (index < 0 || index >= employees.Count)
        {
            ShowInputError("序号超出员工范围。");
            txtIndex.Focus();
            return;
        }

        txtResult.Text = employees[index].GetMessage();
    }

    private bool TryReadCommonFields(out int id, out string name, out int age, out decimal salary)
    {
        id = 0;
        name = txtName.Text.Trim();
        age = 0;
        salary = 0;

        if (!int.TryParse(txtId.Text.Trim(), out id) || id <= 0)
        {
            ShowInputError("工号必须是正整数。");
            txtId.Focus();
            return false;
        }

        if (string.IsNullOrWhiteSpace(name))
        {
            ShowInputError("请输入姓名。");
            txtName.Focus();
            return false;
        }

        if (!int.TryParse(txtAge.Text.Trim(), out age) || age <= 0)
        {
            ShowInputError("年龄必须是正整数。");
            txtAge.Focus();
            return false;
        }

        if (!decimal.TryParse(txtSalary.Text.Trim(), out salary) || salary < 0)
        {
            ShowInputError("工资必须是非负数字。");
            txtSalary.Focus();
            return false;
        }

        return true;
    }

    private void ClearInputs()
    {
        txtId.Clear();
        txtName.Clear();
        txtAge.Clear();
        txtSalary.Clear();
        txtPost.Clear();
        txtDepartment.Clear();
        txtId.Focus();
    }

    private static void ShowInputError(string message)
    {
        MessageBox.Show(message, "输入错误", MessageBoxButtons.OK, MessageBoxIcon.Warning);
    }
}
