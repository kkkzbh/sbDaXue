namespace EmployeeApp;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;
    private Label lblId;
    private Label lblName;
    private Label lblAge;
    private Label lblSalary;
    private Label lblPost;
    private Label lblDepartment;
    private Label lblIndexSuffix;
    private TextBox txtId;
    private TextBox txtName;
    private TextBox txtAge;
    private TextBox txtSalary;
    private TextBox txtPost;
    private TextBox txtDepartment;
    private TextBox txtIndex;
    private TextBox txtResult;
    private Button btnAddStaff;
    private Button btnAddManager;
    private Button btnDisplayAll;
    private Button btnAverage;
    private Button btnSortById;
    private Button btnSortByAge;
    private Button btnFindByName;
    private Button btnShowByIndex;

    /// <summary>
    ///  Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }
        base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    ///  Required method for Designer support - do not modify
    ///  the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        lblId = CreateInputLabel("工号：");
        lblName = CreateInputLabel("姓名：");
        lblAge = CreateInputLabel("年龄：");
        lblSalary = CreateInputLabel("工资：");
        lblPost = CreateInputLabel("岗位：");
        lblDepartment = CreateInputLabel("部门：");
        lblIndexSuffix = CreateInputLabel("条");
        txtId = CreateInputBox();
        txtName = CreateInputBox();
        txtAge = CreateInputBox();
        txtSalary = CreateInputBox();
        txtPost = CreateInputBox();
        txtDepartment = CreateInputBox();
        txtIndex = CreateInputBox();
        txtResult = new TextBox();
        btnAddStaff = CreateCommandButton("添加普通员工");
        btnAddManager = CreateCommandButton("添加管理员工");
        btnDisplayAll = CreateCommandButton("输出所有员工\r\n信息");
        btnAverage = CreateCommandButton("统计普通员工\r\n平均工资");
        btnSortById = CreateCommandButton("按工号升序");
        btnSortByAge = CreateCommandButton("按年龄降序");
        btnFindByName = CreateCommandButton("按姓名查找");
        btnShowByIndex = CreateCommandButton("显示第");
        SuspendLayout();
        //
        // lblId
        //
        lblId.Location = new Point(68, 94);
        //
        // lblName
        //
        lblName.Location = new Point(316, 94);
        //
        // lblAge
        //
        lblAge.Location = new Point(68, 159);
        //
        // lblSalary
        //
        lblSalary.Location = new Point(316, 159);
        //
        // lblPost
        //
        lblPost.Location = new Point(68, 224);
        //
        // lblDepartment
        //
        lblDepartment.Location = new Point(316, 224);
        //
        // lblIndexSuffix
        //
        lblIndexSuffix.Location = new Point(917, 290);
        lblIndexSuffix.Size = new Size(36, 31);
        //
        // txtId
        //
        txtId.Location = new Point(162, 90);
        //
        // txtName
        //
        txtName.Location = new Point(412, 90);
        //
        // txtAge
        //
        txtAge.Location = new Point(162, 155);
        //
        // txtSalary
        //
        txtSalary.Location = new Point(412, 155);
        //
        // txtPost
        //
        txtPost.Location = new Point(162, 220);
        //
        // txtDepartment
        //
        txtDepartment.Location = new Point(412, 220);
        //
        // txtIndex
        //
        txtIndex.Location = new Point(823, 286);
        txtIndex.Size = new Size(81, 31);
        //
        // txtResult
        //
        txtResult.Font = new Font("Microsoft YaHei UI", 11F, FontStyle.Regular, GraphicsUnit.Point, 134);
        txtResult.Location = new Point(106, 340);
        txtResult.Multiline = true;
        txtResult.Name = "txtResult";
        txtResult.ReadOnly = true;
        txtResult.ScrollBars = ScrollBars.Vertical;
        txtResult.Size = new Size(731, 190);
        txtResult.TabIndex = 22;
        //
        // btnAddStaff
        //
        btnAddStaff.Location = new Point(590, 90);
        btnAddStaff.Click += btnAddStaff_Click;
        //
        // btnAddManager
        //
        btnAddManager.Location = new Point(773, 90);
        btnAddManager.Click += btnAddManager_Click;
        //
        // btnDisplayAll
        //
        btnDisplayAll.Location = new Point(590, 187);
        btnDisplayAll.Click += btnDisplayAll_Click;
        //
        // btnAverage
        //
        btnAverage.Location = new Point(773, 187);
        btnAverage.Click += btnAverage_Click;
        //
        // btnSortById
        //
        btnSortById.Location = new Point(80, 277);
        btnSortById.Click += btnSortById_Click;
        //
        // btnSortByAge
        //
        btnSortByAge.Location = new Point(297, 277);
        btnSortByAge.Click += btnSortByAge_Click;
        //
        // btnFindByName
        //
        btnFindByName.Location = new Point(489, 277);
        btnFindByName.Click += btnFindByName_Click;
        //
        // btnShowByIndex
        //
        btnShowByIndex.Location = new Point(682, 277);
        btnShowByIndex.Size = new Size(134, 50);
        btnShowByIndex.Click += btnShowByIndex_Click;
        //
        // Form1
        //
        AutoScaleMode = AutoScaleMode.Font;
        BackColor = Color.WhiteSmoke;
        ClientSize = new Size(978, 544);
        Controls.Add(lblId);
        Controls.Add(lblName);
        Controls.Add(lblAge);
        Controls.Add(lblSalary);
        Controls.Add(lblPost);
        Controls.Add(lblDepartment);
        Controls.Add(lblIndexSuffix);
        Controls.Add(txtId);
        Controls.Add(txtName);
        Controls.Add(txtAge);
        Controls.Add(txtSalary);
        Controls.Add(txtPost);
        Controls.Add(txtDepartment);
        Controls.Add(txtIndex);
        Controls.Add(txtResult);
        Controls.Add(btnAddStaff);
        Controls.Add(btnAddManager);
        Controls.Add(btnDisplayAll);
        Controls.Add(btnAverage);
        Controls.Add(btnSortById);
        Controls.Add(btnSortByAge);
        Controls.Add(btnFindByName);
        Controls.Add(btnShowByIndex);
        Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Regular, GraphicsUnit.Point, 134);
        FormBorderStyle = FormBorderStyle.FixedSingle;
        MaximizeBox = false;
        Name = "Form1";
        StartPosition = FormStartPosition.CenterScreen;
        Text = "员工管理";
        ResumeLayout(false);
        PerformLayout();
    }

    #endregion

    private static Label CreateInputLabel(string text)
    {
        return new Label
        {
            AutoSize = false,
            Font = new Font("SimSun", 18F, FontStyle.Regular, GraphicsUnit.Point, 134),
            Name = "label",
            Size = new Size(88, 31),
            Text = text,
            TextAlign = ContentAlignment.MiddleLeft
        };
    }

    private static TextBox CreateInputBox()
    {
        return new TextBox
        {
            Font = new Font("Microsoft YaHei UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 134),
            Size = new Size(126, 31)
        };
    }

    private static Button CreateCommandButton(string text)
    {
        return new Button
        {
            BackColor = SystemColors.Control,
            Font = new Font("SimSun", 18F, FontStyle.Regular, GraphicsUnit.Point, 134),
            Size = new Size(175, 50),
            Text = text,
            UseVisualStyleBackColor = true
        };
    }
}
