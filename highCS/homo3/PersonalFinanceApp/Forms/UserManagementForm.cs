using PersonalFinanceApp.Data;
using PersonalFinanceApp.UI;

namespace PersonalFinanceApp.Forms;

public sealed class UserManagementForm : Form
{
    private readonly FinanceRepository _repository;
    private readonly DataGridView _grid = new();
    private readonly TextBox _usernameBox = Theme.TextBox("账号");
    private readonly TextBox _displayNameBox = Theme.TextBox("显示名");
    private readonly TextBox _passwordBox = Theme.TextBox("密码");
    private readonly ComboBox _roleBox = Theme.ComboBox();

    public UserManagementForm(FinanceRepository repository)
    {
        _repository = repository;
        Text = "用户管理";
        StartPosition = FormStartPosition.CenterParent;
        Size = new Size(760, 520);
        MinimumSize = new Size(720, 480);
        BackColor = Theme.Background;
        Font = Theme.BodyFont;

        BuildUi();
        RefreshUsers();
    }

    private void BuildUi()
    {
        var root = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(18),
            BackColor = Theme.Background,
            ColumnCount = 2,
            RowCount = 1
        };
        root.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 60));
        root.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 40));
        Controls.Add(root);

        var gridPanel = new Panel { Dock = DockStyle.Fill, BackColor = Theme.Panel, Padding = new Padding(14), Margin = new Padding(8) };
        Theme.StyleGrid(_grid);
        _grid.Dock = DockStyle.Fill;
        _grid.SelectionChanged += (_, _) => LoadSelectedUser();
        gridPanel.Controls.Add(_grid);
        root.Controls.Add(gridPanel, 0, 0);

        var editor = new Panel { Dock = DockStyle.Fill, BackColor = Theme.Panel, Padding = new Padding(18), Margin = new Padding(8) };
        root.Controls.Add(editor, 1, 0);

        var title = Theme.Label("用户资料", Theme.HeadingFont);
        title.Location = new Point(18, 18);
        editor.Controls.Add(title);

        _roleBox.Items.AddRange(["admin", "user"]);
        _roleBox.SelectedIndex = 1;
        Add(editor, Theme.Label("账号", Theme.SmallFont, Theme.Muted), 60);
        Add(editor, _usernameBox, 84);
        Add(editor, Theme.Label("显示名", Theme.SmallFont, Theme.Muted), 126);
        Add(editor, _displayNameBox, 150);
        Add(editor, Theme.Label("密码", Theme.SmallFont, Theme.Muted), 192);
        Add(editor, _passwordBox, 216);
        Add(editor, Theme.Label("角色", Theme.SmallFont, Theme.Muted), 258);
        Add(editor, _roleBox, 282);

        var addButton = Theme.Button("新增用户", Theme.Accent);
        addButton.Click += (_, _) => AddUser();
        Add(editor, addButton, 334);

        var passwordButton = Theme.Button("修改密码");
        passwordButton.Click += (_, _) => UpdatePassword();
        Add(editor, passwordButton, 382);

        var deleteButton = Theme.Button("删除用户");
        deleteButton.Click += (_, _) => DeleteUser();
        Add(editor, deleteButton, 430);
    }

    private void RefreshUsers()
    {
        _grid.DataSource = _repository.GetUsers()
            .Select(u => new { u.Id, 账号 = u.Username, 显示名 = u.DisplayName, 角色 = u.Role })
            .ToList();
        if (_grid.Columns["Id"] is { } column)
        {
            column.Visible = false;
        }
    }

    private void LoadSelectedUser()
    {
        if (_grid.CurrentRow is null)
        {
            return;
        }

        _usernameBox.Text = _grid.CurrentRow.Cells["账号"].Value?.ToString() ?? "";
        _displayNameBox.Text = _grid.CurrentRow.Cells["显示名"].Value?.ToString() ?? "";
        _roleBox.Text = _grid.CurrentRow.Cells["角色"].Value?.ToString() ?? "user";
    }

    private void AddUser()
    {
        if (!ValidateEditor())
        {
            return;
        }

        try
        {
            _repository.AddUser(_usernameBox.Text.Trim(), _passwordBox.Text, _displayNameBox.Text.Trim(), _roleBox.Text);
            ClearEditor();
            RefreshUsers();
        }
        catch (Exception ex)
        {
            MessageBox.Show($"新增用户失败：{ex.Message}", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }

    private void UpdatePassword()
    {
        if (_grid.CurrentRow?.Cells["Id"].Value is not int id)
        {
            MessageBox.Show("请先选择用户。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return;
        }

        if (string.IsNullOrWhiteSpace(_passwordBox.Text))
        {
            MessageBox.Show("请输入新密码。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return;
        }

        _repository.UpdateUserPassword(id, _passwordBox.Text);
        _passwordBox.Clear();
        RefreshUsers();
    }

    private void DeleteUser()
    {
        if (_grid.CurrentRow?.Cells["Id"].Value is not int id)
        {
            MessageBox.Show("请先选择用户。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return;
        }

        _repository.DeleteUser(id);
        ClearEditor();
        RefreshUsers();
    }

    private bool ValidateEditor()
    {
        if (string.IsNullOrWhiteSpace(_usernameBox.Text) || string.IsNullOrWhiteSpace(_passwordBox.Text) || string.IsNullOrWhiteSpace(_displayNameBox.Text))
        {
            MessageBox.Show("账号、显示名和密码都不能为空。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return false;
        }

        return true;
    }

    private void ClearEditor()
    {
        _usernameBox.Clear();
        _displayNameBox.Clear();
        _passwordBox.Clear();
        _roleBox.SelectedIndex = 1;
    }

    private static void Add(Control parent, Control control, int y)
    {
        control.Location = new Point(18, y);
        control.Size = new Size(parent.Width - 36, control.Height);
        control.Anchor = AnchorStyles.Left | AnchorStyles.Right | AnchorStyles.Top;
        parent.Controls.Add(control);
    }
}
