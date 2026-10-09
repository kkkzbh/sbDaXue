namespace ScoreApp;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;
    private Label lblTitle;
    private TableLayoutPanel tableScores;
    private Button btnCalculate;
    private Button btnReset;
    private GroupBox groupResult;
    private Label lblHighestTitle;
    private Label lblLowestTitle;
    private Label lblFinalTitle;
    private Label lblHighestValue;
    private Label lblLowestValue;
    private Label lblFinalValue;
    private NumericUpDown numJudge1;
    private NumericUpDown numJudge2;
    private NumericUpDown numJudge3;
    private NumericUpDown numJudge4;
    private NumericUpDown numJudge5;
    private NumericUpDown numJudge6;
    private NumericUpDown numJudge7;
    private NumericUpDown numJudge8;
    private NumericUpDown numJudge9;
    private NumericUpDown numJudge10;

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
        lblTitle = new Label();
        tableScores = new TableLayoutPanel();
        numJudge1 = CreateScoreInput();
        numJudge2 = CreateScoreInput();
        numJudge3 = CreateScoreInput();
        numJudge4 = CreateScoreInput();
        numJudge5 = CreateScoreInput();
        numJudge6 = CreateScoreInput();
        numJudge7 = CreateScoreInput();
        numJudge8 = CreateScoreInput();
        numJudge9 = CreateScoreInput();
        numJudge10 = CreateScoreInput();
        btnCalculate = new Button();
        btnReset = new Button();
        groupResult = new GroupBox();
        lblHighestTitle = new Label();
        lblLowestTitle = new Label();
        lblFinalTitle = new Label();
        lblHighestValue = new Label();
        lblLowestValue = new Label();
        lblFinalValue = new Label();
        tableScores.SuspendLayout();
        groupResult.SuspendLayout();
        SuspendLayout();
        //
        // lblTitle
        //
        lblTitle.AutoSize = true;
        lblTitle.Font = new Font("Microsoft YaHei UI", 14.25F, FontStyle.Bold, GraphicsUnit.Point, 134);
        lblTitle.Location = new Point(27, 20);
        lblTitle.Name = "lblTitle";
        lblTitle.Size = new Size(259, 26);
        lblTitle.TabIndex = 0;
        lblTitle.Text = "选手评分计算器（10位评委）";
        //
        // tableScores
        //
        tableScores.ColumnCount = 4;
        tableScores.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 80F));
        tableScores.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 120F));
        tableScores.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 80F));
        tableScores.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 120F));
        tableScores.Controls.Add(CreateJudgeLabel("评委1"), 0, 0);
        tableScores.Controls.Add(numJudge1, 1, 0);
        tableScores.Controls.Add(CreateJudgeLabel("评委2"), 2, 0);
        tableScores.Controls.Add(numJudge2, 3, 0);
        tableScores.Controls.Add(CreateJudgeLabel("评委3"), 0, 1);
        tableScores.Controls.Add(numJudge3, 1, 1);
        tableScores.Controls.Add(CreateJudgeLabel("评委4"), 2, 1);
        tableScores.Controls.Add(numJudge4, 3, 1);
        tableScores.Controls.Add(CreateJudgeLabel("评委5"), 0, 2);
        tableScores.Controls.Add(numJudge5, 1, 2);
        tableScores.Controls.Add(CreateJudgeLabel("评委6"), 2, 2);
        tableScores.Controls.Add(numJudge6, 3, 2);
        tableScores.Controls.Add(CreateJudgeLabel("评委7"), 0, 3);
        tableScores.Controls.Add(numJudge7, 1, 3);
        tableScores.Controls.Add(CreateJudgeLabel("评委8"), 2, 3);
        tableScores.Controls.Add(numJudge8, 3, 3);
        tableScores.Controls.Add(CreateJudgeLabel("评委9"), 0, 4);
        tableScores.Controls.Add(numJudge9, 1, 4);
        tableScores.Controls.Add(CreateJudgeLabel("评委10"), 2, 4);
        tableScores.Controls.Add(numJudge10, 3, 4);
        tableScores.Location = new Point(31, 61);
        tableScores.Name = "tableScores";
        tableScores.RowCount = 5;
        tableScores.RowStyles.Add(new RowStyle(SizeType.Absolute, 44F));
        tableScores.RowStyles.Add(new RowStyle(SizeType.Absolute, 44F));
        tableScores.RowStyles.Add(new RowStyle(SizeType.Absolute, 44F));
        tableScores.RowStyles.Add(new RowStyle(SizeType.Absolute, 44F));
        tableScores.RowStyles.Add(new RowStyle(SizeType.Absolute, 44F));
        tableScores.Size = new Size(400, 220);
        tableScores.TabIndex = 1;
        //
        // btnCalculate
        //
        btnCalculate.BackColor = Color.SteelBlue;
        btnCalculate.FlatStyle = FlatStyle.Flat;
        btnCalculate.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Bold, GraphicsUnit.Point, 134);
        btnCalculate.ForeColor = Color.White;
        btnCalculate.Location = new Point(31, 299);
        btnCalculate.Name = "btnCalculate";
        btnCalculate.Size = new Size(126, 40);
        btnCalculate.TabIndex = 2;
        btnCalculate.Text = "计算成绩";
        btnCalculate.UseVisualStyleBackColor = false;
        btnCalculate.Click += btnCalculate_Click;
        //
        // btnReset
        //
        btnReset.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Regular, GraphicsUnit.Point, 134);
        btnReset.Location = new Point(177, 299);
        btnReset.Name = "btnReset";
        btnReset.Size = new Size(126, 40);
        btnReset.TabIndex = 3;
        btnReset.Text = "重置";
        btnReset.UseVisualStyleBackColor = true;
        btnReset.Click += btnReset_Click;
        //
        // groupResult
        //
        groupResult.Controls.Add(lblHighestTitle);
        groupResult.Controls.Add(lblLowestTitle);
        groupResult.Controls.Add(lblFinalTitle);
        groupResult.Controls.Add(lblHighestValue);
        groupResult.Controls.Add(lblLowestValue);
        groupResult.Controls.Add(lblFinalValue);
        groupResult.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Bold, GraphicsUnit.Point, 134);
        groupResult.Location = new Point(456, 61);
        groupResult.Name = "groupResult";
        groupResult.Size = new Size(219, 220);
        groupResult.TabIndex = 4;
        groupResult.TabStop = false;
        groupResult.Text = "计算结果";
        //
        // lblHighestTitle
        //
        lblHighestTitle.AutoSize = true;
        lblHighestTitle.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Regular, GraphicsUnit.Point, 134);
        lblHighestTitle.Location = new Point(24, 42);
        lblHighestTitle.Name = "lblHighestTitle";
        lblHighestTitle.Size = new Size(65, 20);
        lblHighestTitle.TabIndex = 0;
        lblHighestTitle.Text = "最高分：";
        //
        // lblLowestTitle
        //
        lblLowestTitle.AutoSize = true;
        lblLowestTitle.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Regular, GraphicsUnit.Point, 134);
        lblLowestTitle.Location = new Point(24, 92);
        lblLowestTitle.Name = "lblLowestTitle";
        lblLowestTitle.Size = new Size(65, 20);
        lblLowestTitle.TabIndex = 1;
        lblLowestTitle.Text = "最低分：";
        //
        // lblFinalTitle
        //
        lblFinalTitle.AutoSize = true;
        lblFinalTitle.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Regular, GraphicsUnit.Point, 134);
        lblFinalTitle.Location = new Point(24, 142);
        lblFinalTitle.Name = "lblFinalTitle";
        lblFinalTitle.Size = new Size(65, 20);
        lblFinalTitle.TabIndex = 2;
        lblFinalTitle.Text = "最终分：";
        //
        // lblHighestValue
        //
        lblHighestValue.AutoSize = true;
        lblHighestValue.Font = new Font("Microsoft YaHei UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 134);
        lblHighestValue.ForeColor = Color.DarkSlateBlue;
        lblHighestValue.Location = new Point(108, 40);
        lblHighestValue.Name = "lblHighestValue";
        lblHighestValue.Size = new Size(16, 22);
        lblHighestValue.TabIndex = 3;
        lblHighestValue.Text = "-";
        //
        // lblLowestValue
        //
        lblLowestValue.AutoSize = true;
        lblLowestValue.Font = new Font("Microsoft YaHei UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 134);
        lblLowestValue.ForeColor = Color.DarkSlateBlue;
        lblLowestValue.Location = new Point(108, 90);
        lblLowestValue.Name = "lblLowestValue";
        lblLowestValue.Size = new Size(16, 22);
        lblLowestValue.TabIndex = 4;
        lblLowestValue.Text = "-";
        //
        // lblFinalValue
        //
        lblFinalValue.AutoSize = true;
        lblFinalValue.Font = new Font("Microsoft YaHei UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 134);
        lblFinalValue.ForeColor = Color.Firebrick;
        lblFinalValue.Location = new Point(108, 140);
        lblFinalValue.Name = "lblFinalValue";
        lblFinalValue.Size = new Size(16, 22);
        lblFinalValue.TabIndex = 5;
        lblFinalValue.Text = "-";
        //
        // Form1
        //
        AutoScaleDimensions = new SizeF(7F, 17F);
        AutoScaleMode = AutoScaleMode.Font;
        BackColor = Color.WhiteSmoke;
        ClientSize = new Size(710, 372);
        Controls.Add(groupResult);
        Controls.Add(btnReset);
        Controls.Add(btnCalculate);
        Controls.Add(tableScores);
        Controls.Add(lblTitle);
        FormBorderStyle = FormBorderStyle.FixedSingle;
        MaximizeBox = false;
        Name = "Form1";
        StartPosition = FormStartPosition.CenterScreen;
        Text = "作业1 - 选手评分";
        tableScores.ResumeLayout(false);
        tableScores.PerformLayout();
        groupResult.ResumeLayout(false);
        groupResult.PerformLayout();
        ResumeLayout(false);
        PerformLayout();
    }

    private static Label CreateJudgeLabel(string text)
    {
        return new Label
        {
            Anchor = AnchorStyles.Left,
            AutoSize = true,
            Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Regular, GraphicsUnit.Point, 134),
            Text = text
        };
    }

    private static NumericUpDown CreateScoreInput()
    {
        return new NumericUpDown
        {
            Anchor = AnchorStyles.Left,
            DecimalPlaces = 0,
            Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Regular, GraphicsUnit.Point, 134),
            Location = new Point(3, 10),
            Maximum = 10,
            Minimum = 1,
            Size = new Size(96, 25),
            Value = 1
        };
    }

    #endregion
}
