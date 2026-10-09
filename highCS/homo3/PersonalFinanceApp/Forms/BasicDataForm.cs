using Microsoft.Data.Sqlite;
using PersonalFinanceApp.Data;
using PersonalFinanceApp.Models;
using PersonalFinanceApp.UI;

namespace PersonalFinanceApp.Forms;

public sealed class BasicDataForm : Form
{
    private readonly FinanceRepository _repository;
    private readonly DataGridView _categoryGrid = new();
    private readonly DataGridView _itemGrid = new();
    private readonly DataGridView _personGrid = new();
    private readonly ComboBox _typeBox = Theme.ComboBox();
    private readonly TextBox _categoryNameBox = Theme.TextBox("类别名称");
    private readonly ComboBox _itemCategoryBox = Theme.ComboBox();
    private readonly TextBox _itemNameBox = Theme.TextBox("项目名称");
    private readonly TextBox _personNameBox = Theme.TextBox("收支人姓名");

    public BasicDataForm(FinanceRepository repository)
    {
        _repository = repository;
        Text = "基本资料管理";
        StartPosition = FormStartPosition.CenterParent;
        Size = new Size(980, 620);
        MinimumSize = new Size(900, 560);
        BackColor = Theme.Background;
        Font = Theme.BodyFont;

        BuildUi();
        RefreshData();
    }

    private void BuildUi()
    {
        var root = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(18),
            BackColor = Theme.Background,
            ColumnCount = 3,
            RowCount = 1
        };
        root.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 34));
        root.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 34));
        root.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 32));
        Controls.Add(root);

        root.Controls.Add(BuildCategoryPanel(), 0, 0);
        root.Controls.Add(BuildItemPanel(), 1, 0);
        root.Controls.Add(BuildPersonPanel(), 2, 0);
    }

    private Control BuildCategoryPanel()
    {
        var panel = Section("收支类别管理");
        _typeBox.Items.AddRange(["收入", "支出"]);
        _typeBox.SelectedIndex = 0;
        AddControl(panel, Theme.Label("类型", Theme.SmallFont, Theme.Muted), 48);
        AddControl(panel, _typeBox, 72);
        AddControl(panel, Theme.Label("类别名称", Theme.SmallFont, Theme.Muted), 112);
        AddControl(panel, _categoryNameBox, 136);
        var addButton = Theme.Button("新增类别", Theme.Accent);
        addButton.Click += (_, _) =>
        {
            if (RequireText(_categoryNameBox, "请输入类别名称。"))
            {
                _repository.AddCategory(_categoryNameBox.Text.Trim(), _typeBox.Text);
                _categoryNameBox.Clear();
                RefreshData();
            }
        };
        AddControl(panel, addButton, 180);

        var deleteButton = Theme.Button("删除选中类别");
        deleteButton.Click += (_, _) => DeleteSelected(_categoryGrid, id => _repository.DeleteCategory(id));
        AddControl(panel, deleteButton, 226);

        Theme.StyleGrid(_categoryGrid);
        _categoryGrid.Location = new Point(16, 282);
        _categoryGrid.Size = new Size(280, 260);
        _categoryGrid.Anchor = AnchorStyles.Left | AnchorStyles.Top | AnchorStyles.Right | AnchorStyles.Bottom;
        panel.Controls.Add(_categoryGrid);
        return panel;
    }

    private Control BuildItemPanel()
    {
        var panel = Section("收支项目管理");
        AddControl(panel, Theme.Label("所属类别", Theme.SmallFont, Theme.Muted), 48);
        AddControl(panel, _itemCategoryBox, 72);
        AddControl(panel, Theme.Label("项目名称", Theme.SmallFont, Theme.Muted), 112);
        AddControl(panel, _itemNameBox, 136);

        var addButton = Theme.Button("新增项目", Theme.Accent);
        addButton.Click += (_, _) =>
        {
            if (_itemCategoryBox.SelectedItem is Category category && RequireText(_itemNameBox, "请输入项目名称。"))
            {
                _repository.AddItem(category.Id, _itemNameBox.Text.Trim(), category.Type);
                _itemNameBox.Clear();
                RefreshData();
            }
        };
        AddControl(panel, addButton, 180);

        var deleteButton = Theme.Button("删除选中项目");
        deleteButton.Click += (_, _) => DeleteSelected(_itemGrid, id => _repository.DeleteItem(id));
        AddControl(panel, deleteButton, 226);

        Theme.StyleGrid(_itemGrid);
        _itemGrid.Location = new Point(16, 282);
        _itemGrid.Size = new Size(280, 260);
        _itemGrid.Anchor = AnchorStyles.Left | AnchorStyles.Top | AnchorStyles.Right | AnchorStyles.Bottom;
        panel.Controls.Add(_itemGrid);
        return panel;
    }

    private Control BuildPersonPanel()
    {
        var panel = Section("收支人管理");
        AddControl(panel, Theme.Label("姓名", Theme.SmallFont, Theme.Muted), 48);
        AddControl(panel, _personNameBox, 72);

        var addButton = Theme.Button("新增收支人", Theme.Accent);
        addButton.Click += (_, _) =>
        {
            if (RequireText(_personNameBox, "请输入收支人姓名。"))
            {
                _repository.AddPerson(_personNameBox.Text.Trim());
                _personNameBox.Clear();
                RefreshData();
            }
        };
        AddControl(panel, addButton, 118);

        var deleteButton = Theme.Button("删除选中收支人");
        deleteButton.Click += (_, _) => DeleteSelected(_personGrid, id => _repository.DeletePerson(id));
        AddControl(panel, deleteButton, 164);

        Theme.StyleGrid(_personGrid);
        _personGrid.Location = new Point(16, 222);
        _personGrid.Size = new Size(260, 320);
        _personGrid.Anchor = AnchorStyles.Left | AnchorStyles.Top | AnchorStyles.Right | AnchorStyles.Bottom;
        panel.Controls.Add(_personGrid);
        return panel;
    }

    private void RefreshData()
    {
        var categories = _repository.GetCategories();
        _categoryGrid.DataSource = categories.Select(c => new { c.Id, 类型 = c.Type, 类别 = c.Name }).ToList();
        HideId(_categoryGrid);

        _itemCategoryBox.DataSource = categories.ToList();
        _itemCategoryBox.DisplayMember = nameof(Category.Name);
        _itemCategoryBox.ValueMember = nameof(Category.Id);

        _itemGrid.DataSource = _repository.GetItems().Select(i => new { i.Id, 类型 = i.Type, 项目 = i.Name, 类别编号 = i.CategoryId }).ToList();
        HideId(_itemGrid);

        _personGrid.DataSource = _repository.GetPeople().Select(p => new { p.Id, 姓名 = p.Name }).ToList();
        HideId(_personGrid);
    }

    private static Panel Section(string title)
    {
        var panel = new Panel
        {
            Dock = DockStyle.Fill,
            Margin = new Padding(8),
            Padding = new Padding(16),
            BackColor = Theme.Panel
        };
        var label = Theme.Label(title, Theme.HeadingFont);
        label.Location = new Point(16, 16);
        panel.Controls.Add(label);
        return panel;
    }

    private static void AddControl(Control parent, Control control, int y)
    {
        control.Location = new Point(16, y);
        control.Size = new Size(parent.Width - 32, control.Height);
        control.Anchor = AnchorStyles.Left | AnchorStyles.Top | AnchorStyles.Right;
        parent.Controls.Add(control);
    }

    private static bool RequireText(TextBox box, string message)
    {
        if (!string.IsNullOrWhiteSpace(box.Text))
        {
            return true;
        }

        MessageBox.Show(message, "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
        return false;
    }

    private void DeleteSelected(DataGridView grid, Action<int> delete)
    {
        if (grid.CurrentRow?.Cells["Id"].Value is not int id)
        {
            MessageBox.Show("请先选择要删除的数据。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return;
        }

        try
        {
            delete(id);
            RefreshData();
        }
        catch (SqliteException)
        {
            MessageBox.Show("该资料已经被收支记录使用，不能直接删除。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }

    private static void HideId(DataGridView grid)
    {
        if (grid.Columns["Id"] is { } column)
        {
            column.Visible = false;
        }
    }
}
