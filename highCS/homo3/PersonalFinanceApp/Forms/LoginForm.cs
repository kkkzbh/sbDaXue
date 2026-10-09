using PersonalFinanceApp.Data;
using PersonalFinanceApp.Models;
using PersonalFinanceApp.UI;

namespace PersonalFinanceApp.Forms;

public sealed class LoginForm : Form
{
    private readonly FinanceRepository _repository;
    private readonly TextBox _usernameBox = Theme.TextBox("请输入账号");
    private readonly TextBox _passwordBox = Theme.TextBox("请输入密码");

    public LoginForm(FinanceRepository repository)
    {
        _repository = repository;
        Text = "个人理财系统 - 登录";
        StartPosition = FormStartPosition.CenterScreen;
        Size = new Size(460, 360);
        MinimumSize = new Size(460, 360);
        BackColor = Theme.Background;
        Font = Theme.BodyFont;

        BuildUi();
    }

    private void BuildUi()
    {
        var card = new Panel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(42),
            BackColor = Theme.Background
        };
        Controls.Add(card);

        var title = Theme.Label("个人理财系统", Theme.TitleFont);
        var subtitle = Theme.Label("默认账号 admin / 123456", Theme.SmallFont, Theme.Muted);

        _usernameBox.Text = "admin";
        _passwordBox.Text = "123456";
        _passwordBox.UseSystemPasswordChar = true;

        var loginButton = Theme.Button("登录", Theme.Accent);
        loginButton.Click += (_, _) => Login();

        var exitButton = Theme.Button("退出");
        exitButton.Click += (_, _) => Close();

        var layout = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            ColumnCount = 1,
            RowCount = 8,
            BackColor = Theme.Background
        };
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 42));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 30));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 32));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 48));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 32));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 48));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 56));
        layout.RowStyles.Add(new RowStyle(SizeType.Absolute, 44));
        card.Controls.Add(layout);

        layout.Controls.Add(title, 0, 0);
        layout.Controls.Add(subtitle, 0, 1);
        layout.Controls.Add(Theme.Label("账号", Theme.SmallFont, Theme.Muted), 0, 2);
        layout.Controls.Add(_usernameBox, 0, 3);
        layout.Controls.Add(Theme.Label("密码", Theme.SmallFont, Theme.Muted), 0, 4);
        layout.Controls.Add(_passwordBox, 0, 5);
        layout.Controls.Add(loginButton, 0, 6);
        layout.Controls.Add(exitButton, 0, 7);

        AcceptButton = loginButton;
        CancelButton = exitButton;
    }

    private void Login()
    {
        User? user = _repository.Authenticate(_usernameBox.Text.Trim(), _passwordBox.Text);
        if (user is null)
        {
            MessageBox.Show("账号或密码错误。", "登录失败", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            return;
        }

        Hide();
        using var mainForm = new MainForm(_repository, user);
        mainForm.ShowDialog(this);
        Close();
    }
}
