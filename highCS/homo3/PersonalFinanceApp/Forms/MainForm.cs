using PersonalFinanceApp.Data;
using PersonalFinanceApp.Models;
using PersonalFinanceApp.UI;

namespace PersonalFinanceApp.Forms;

public sealed class MainForm : Form
{
    private readonly FinanceRepository _repository;
    private readonly User _currentUser;
    private readonly DataGridView _grid = new();
    private readonly TextBox _searchBox = Theme.TextBox("搜索记录、类别或收支人");
    private readonly ComboBox _categoryBox = Theme.ComboBox();
    private readonly ComboBox _itemBox = Theme.ComboBox();
    private readonly ComboBox _personBox = Theme.ComboBox();
    private readonly DateTimePicker _datePicker = new();
    private readonly TextBox _amountBox = Theme.TextBox("请输入金额");
    private readonly TextBox _noteBox = Theme.TextBox("请输入说明（可选）");
    private readonly Label _incomeValue = Theme.Label("¥0.00", Theme.TitleFont, Theme.Income);
    private readonly Label _expenseValue = Theme.Label("¥0.00", Theme.TitleFont, Theme.Expense);
    private readonly Label _balanceValue = Theme.Label("¥0.00", Theme.TitleFont, Theme.Text);
    private readonly Label _countValue = Theme.Label("0", Theme.TitleFont, Theme.Text);
    private readonly Label _totalLabel = Theme.Label("共 0 条记录", Theme.SmallFont, Theme.Muted);
    private readonly Button _incomeButton = Theme.Button("↓ 收入", Theme.Accent);
    private readonly Button _expenseButton = Theme.Button("↑ 支出");
    private readonly Button _allFilter = Theme.Button("全部", Theme.Accent);
    private readonly Button _incomeFilter = Theme.Button("收入");
    private readonly Button _expenseFilter = Theme.Button("支出");
    private readonly Button _monthFilter = Theme.Button("本月");
    private string _recordType = "收入";
    private string _filterType = "全部";
    private bool _onlyMonth;
    private int? _editingId;
    private List<TransactionRecord> _records = [];
    private bool _isRefreshingGrid;

    public MainForm(FinanceRepository repository, User currentUser)
    {
        _repository = repository;
        _currentUser = currentUser;
        Text = "个人理财系统";
        StartPosition = FormStartPosition.CenterScreen;
        Size = new Size(1380, 820);
        MinimumSize = new Size(1180, 720);
        BackColor = Theme.Background;
        Font = Theme.BodyFont;

        BuildUi();
        LoadLookups();
        RefreshAll();
    }

    private void BuildUi()
    {
        var shell = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            ColumnCount = 3,
            RowCount = 1,
            BackColor = Theme.Background
        };
        shell.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 250));
        shell.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
        shell.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 330));
        Controls.Add(shell);

        shell.Controls.Add(BuildSidebar(), 0, 0);
        shell.Controls.Add(BuildCenter(), 1, 0);
        shell.Controls.Add(BuildEditor(), 2, 0);
    }

    private Control BuildSidebar()
    {
        var sidebar = new Panel
        {
            Dock = DockStyle.Fill,
            BackColor = Theme.Sidebar,
            Padding = new Padding(16, 24, 16, 20)
        };

        var title = Theme.Label("个人理财系统", Theme.TitleFont);
        title.Location = new Point(56, 18);
        sidebar.Controls.Add(title);

        var icon = new Label
        {
            Text = "💳",
            Location = new Point(14, 16),
            Size = new Size(40, 40),
            TextAlign = ContentAlignment.MiddleCenter,
            BackColor = Color.FromArgb(42, 57, 88),
            ForeColor = Theme.Text,
            Font = new Font("Segoe UI Emoji", 18F)
        };
        sidebar.Controls.Add(icon);

        var items = new[]
        {
            ("⌂  概览", (Action)(() => RefreshAll())),
            ("▤  收支记录", (Action)(() => RefreshAll())),
            ("＋  新增收支", (Action)ClearEditor),
            ("□  基本资料", (Action)OpenBasicData),
            ("♙  用户管理", (Action)OpenUserManagement),
            ("⚙  设置", (Action)(() => MessageBox.Show($"数据库位置：{_repository.DatabasePath}", "设置"))),
            ("↪  退出", (Action)Close)
        };

        var top = 86;
        foreach (var (text, action) in items)
        {
            var button = Theme.Button(text);
            button.TextAlign = ContentAlignment.MiddleLeft;
            button.Location = new Point(0, top);
            button.Size = new Size(216, 44);
            button.FlatAppearance.BorderColor = Theme.Sidebar;
            button.Click += (_, _) => action();
            sidebar.Controls.Add(button);
            top += text.Contains("退出") ? 66 : 52;
        }

        var summary = new Panel
        {
            Anchor = AnchorStyles.Left | AnchorStyles.Right | AnchorStyles.Bottom,
            Location = new Point(16, 640),
            Size = new Size(216, 92),
            BackColor = Theme.Panel,
            Padding = new Padding(16)
        };
        summary.Controls.Add(Theme.Label("本月结余", Theme.SmallFont, Theme.Muted));
        var sideBalance = Theme.Label("见概览", Theme.HeadingFont);
        sideBalance.Location = new Point(16, 38);
        summary.Controls.Add(sideBalance);
        sidebar.Controls.Add(summary);

        return sidebar;
    }

    private Control BuildCenter()
    {
        var center = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            BackColor = Theme.Background,
            Padding = new Padding(18),
            RowCount = 4,
            ColumnCount = 1
        };
        center.RowStyles.Add(new RowStyle(SizeType.Absolute, 64));
        center.RowStyles.Add(new RowStyle(SizeType.Absolute, 120));
        center.RowStyles.Add(new RowStyle(SizeType.Absolute, 64));
        center.RowStyles.Add(new RowStyle(SizeType.Percent, 100));

        center.Controls.Add(BuildTopbar(), 0, 0);
        center.Controls.Add(BuildStats(), 0, 1);
        center.Controls.Add(BuildFilters(), 0, 2);
        center.Controls.Add(BuildGridPanel(), 0, 3);
        return center;
    }

    private Control BuildTopbar()
    {
        var bar = new Panel { Dock = DockStyle.Fill, BackColor = Theme.Background };
        _searchBox.Location = new Point(0, 10);
        _searchBox.Size = new Size(560, 34);
        _searchBox.TextChanged += (_, _) => RefreshGrid();
        bar.Controls.Add(_searchBox);

        var user = Theme.Label($"●  {_currentUser.DisplayName}", Theme.HeadingFont);
        user.Anchor = AnchorStyles.Top | AnchorStyles.Right;
        user.Location = new Point(700, 14);
        user.AutoSize = true;
        bar.Controls.Add(user);
        return bar;
    }

    private Control BuildStats()
    {
        var stats = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            ColumnCount = 4,
            RowCount = 1,
            BackColor = Theme.Background
        };
        for (var i = 0; i < 4; i++)
        {
            stats.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25));
        }

        stats.Controls.Add(StatCard("本月收入", _incomeValue, "较上月 +12.4% ↑", Theme.Income), 0, 0);
        stats.Controls.Add(StatCard("本月支出", _expenseValue, "较上月 -5.7% ↓", Theme.Expense), 1, 0);
        stats.Controls.Add(StatCard("结余", _balanceValue, "较上月 +18.1% ↑", Theme.Blue), 2, 0);
        stats.Controls.Add(StatCard("记录", _countValue, "本月记录数", Color.FromArgb(119, 103, 175)), 3, 0);
        return stats;
    }

    private Control StatCard(string title, Label valueLabel, string note, Color accent)
    {
        var panel = new Panel
        {
            Dock = DockStyle.Fill,
            Margin = new Padding(0, 8, 14, 10),
            BackColor = Theme.Panel,
            Padding = new Padding(18)
        };

        var dot = new Label
        {
            Text = "●",
            ForeColor = accent,
            Font = new Font("Segoe UI", 24F),
            Location = new Point(16, 28),
            Size = new Size(42, 42),
            TextAlign = ContentAlignment.MiddleCenter
        };
        panel.Controls.Add(dot);

        valueLabel.Font = new Font("Microsoft YaHei UI", 13.5F, FontStyle.Bold);
        var titleLabel = Theme.Label(title, Theme.SmallFont, Theme.Muted);
        titleLabel.Location = new Point(58, 24);
        valueLabel.Location = new Point(58, 46);
        var noteLabel = Theme.Label(note, Theme.SmallFont, accent);
        noteLabel.Location = new Point(58, 78);
        panel.Controls.Add(titleLabel);
        panel.Controls.Add(valueLabel);
        panel.Controls.Add(noteLabel);
        return panel;
    }

    private Control BuildFilters()
    {
        var wrap = new Panel { Dock = DockStyle.Fill, BackColor = Theme.Background };
        var title = Theme.Label("收支明细", Theme.HeadingFont);
        title.Location = new Point(0, 6);
        wrap.Controls.Add(title);

        var buttons = new[] { _allFilter, _incomeFilter, _expenseFilter, _monthFilter };
        var x = 0;
        foreach (var button in buttons)
        {
            button.Location = new Point(x, 34);
            button.Size = new Size(72, 34);
            wrap.Controls.Add(button);
            x += 82;
        }

        _allFilter.Click += (_, _) => SetFilter("全部", false);
        _incomeFilter.Click += (_, _) => SetFilter("收入", false);
        _expenseFilter.Click += (_, _) => SetFilter("支出", false);
        _monthFilter.Click += (_, _) => SetFilter(_filterType, !_onlyMonth);
        return wrap;
    }

    private Control BuildGridPanel()
    {
        var panel = new Panel
        {
            Dock = DockStyle.Fill,
            BackColor = Theme.Panel,
            Padding = new Padding(14)
        };

        Theme.StyleGrid(_grid);
        _grid.Dock = DockStyle.Fill;
        _grid.CellFormatting += GridCellFormatting;
        _grid.SelectionChanged += (_, _) => LoadSelectedRecord();
        panel.Controls.Add(_grid);

        _totalLabel.Dock = DockStyle.Bottom;
        panel.Controls.Add(_totalLabel);
        return panel;
    }

    private Control BuildEditor()
    {
        var editor = new Panel
        {
            Dock = DockStyle.Fill,
            BackColor = Theme.Panel,
            Padding = new Padding(22)
        };

        var title = Theme.Label("新增收支记录", Theme.HeadingFont);
        title.Location = new Point(22, 28);
        editor.Controls.Add(title);

        var y = 76;
        AddLabel(editor, "类型", ref y);
        _incomeButton.Location = new Point(22, y);
        _incomeButton.Size = new Size(140, 40);
        _expenseButton.Location = new Point(164, y);
        _expenseButton.Size = new Size(140, 40);
        _incomeButton.Click += (_, _) => SetRecordType("收入");
        _expenseButton.Click += (_, _) => SetRecordType("支出");
        editor.Controls.Add(_incomeButton);
        editor.Controls.Add(_expenseButton);
        y += 56;

        AddField(editor, "类别", _categoryBox, ref y);
        _categoryBox.SelectedIndexChanged += (_, _) => LoadItemsForCategory();
        AddField(editor, "项目", _itemBox, ref y);

        AddLabel(editor, "日期", ref y);
        _datePicker.Location = new Point(22, y);
        _datePicker.Size = new Size(282, 30);
        _datePicker.Format = DateTimePickerFormat.Custom;
        _datePicker.CustomFormat = "yyyy-MM-dd";
        _datePicker.CalendarMonthBackground = Theme.PanelSoft;
        editor.Controls.Add(_datePicker);
        y += 56;

        AddField(editor, "金额", _amountBox, ref y);
        AddField(editor, "收支人", _personBox, ref y);
        AddField(editor, "说明", _noteBox, ref y);

        var hint = Theme.Label("类别与项目可在基本资料中维护", Theme.SmallFont, Theme.Muted);
        hint.Location = new Point(22, 590);
        editor.Controls.Add(hint);

        var clearButton = Theme.Button("清空");
        clearButton.Location = new Point(22, 640);
        clearButton.Size = new Size(86, 42);
        clearButton.Click += (_, _) => ClearEditor();
        editor.Controls.Add(clearButton);

        var deleteButton = Theme.Button("删除");
        deleteButton.Location = new Point(116, 640);
        deleteButton.Size = new Size(86, 42);
        deleteButton.Click += (_, _) => DeleteSelectedRecord();
        editor.Controls.Add(deleteButton);

        var saveButton = Theme.Button("保存记录", Theme.Accent);
        saveButton.Location = new Point(210, 640);
        saveButton.Size = new Size(94, 42);
        saveButton.Click += (_, _) => SaveRecord();
        editor.Controls.Add(saveButton);
        return editor;
    }

    private static void AddLabel(Control parent, string text, ref int y)
    {
        var label = Theme.Label(text, Theme.SmallFont, Theme.Muted);
        label.Location = new Point(22, y);
        parent.Controls.Add(label);
        y += 24;
    }

    private static void AddField(Control parent, string label, Control control, ref int y)
    {
        AddLabel(parent, label, ref y);
        control.Location = new Point(22, y);
        control.Size = new Size(282, 32);
        parent.Controls.Add(control);
        y += 58;
    }

    private void LoadLookups()
    {
        _personBox.DataSource = _repository.GetPeople();
        _personBox.DisplayMember = nameof(Person.Name);
        _personBox.ValueMember = nameof(Person.Id);
        SetRecordType(_recordType);
    }

    private void LoadCategories()
    {
        var selectedId = (_categoryBox.SelectedItem as Category)?.Id;
        _categoryBox.DataSource = _repository.GetCategories(_recordType);
        _categoryBox.DisplayMember = nameof(Category.Name);
        _categoryBox.ValueMember = nameof(Category.Id);
        if (selectedId is not null)
        {
            foreach (Category category in _categoryBox.Items)
            {
                if (category.Id == selectedId)
                {
                    _categoryBox.SelectedItem = category;
                    break;
                }
            }
        }
    }

    private void LoadItemsForCategory()
    {
        if (_categoryBox.SelectedItem is not Category category)
        {
            _itemBox.DataSource = null;
            return;
        }

        _itemBox.DataSource = _repository.GetItems(category.Id);
        _itemBox.DisplayMember = nameof(FinanceItem.Name);
        _itemBox.ValueMember = nameof(FinanceItem.Id);
    }

    private void RefreshAll()
    {
        RefreshSummary();
        RefreshGrid();
    }

    private void RefreshSummary()
    {
        var summary = _repository.GetMonthlySummary();
        _incomeValue.Text = Money(summary.Income);
        _expenseValue.Text = Money(summary.Expense);
        _balanceValue.Text = Money(summary.Balance);
        _countValue.Text = summary.Count.ToString();
    }

    private void RefreshGrid()
    {
        _isRefreshingGrid = true;
        _records = _repository.GetTransactions(_filterType, _onlyMonth, _searchBox.Text);
        _grid.DataSource = _records.Select(record => new
        {
            record.Id,
            日期 = record.Date.ToString("yyyy-MM-dd"),
            类型 = record.Type,
            类别 = record.CategoryName,
            项目 = record.ItemName,
            收支人 = record.PersonName,
            金额 = record.Type == "收入" ? $"+{Money(record.Amount)}" : $"-{Money(record.Amount)}",
            备注 = record.Note
        }).ToList();
        if (_grid.Columns["Id"] is { } idColumn)
        {
            idColumn.Visible = false;
        }

        _totalLabel.Text = $"共 {_records.Count} 条记录";
        _grid.ClearSelection();
        _editingId = null;
        _isRefreshingGrid = false;
    }

    private void SetFilter(string type, bool month)
    {
        _filterType = type;
        _onlyMonth = month;
        _allFilter.BackColor = type == "全部" && !month ? Theme.Accent : Theme.PanelSoft;
        _incomeFilter.BackColor = type == "收入" && !month ? Theme.Accent : Theme.PanelSoft;
        _expenseFilter.BackColor = type == "支出" && !month ? Theme.Accent : Theme.PanelSoft;
        _monthFilter.BackColor = month ? Theme.Accent : Theme.PanelSoft;
        RefreshGrid();
    }

    private void SetRecordType(string type)
    {
        _recordType = type;
        _incomeButton.BackColor = type == "收入" ? Theme.Accent : Theme.PanelSoft;
        _expenseButton.BackColor = type == "支出" ? Theme.Expense : Theme.PanelSoft;
        LoadCategories();
    }

    private void LoadSelectedRecord()
    {
        if (_isRefreshingGrid || _grid.SelectedRows.Count == 0 || _grid.CurrentRow?.Cells["Id"].Value is not int id)
        {
            return;
        }

        var record = _records.FirstOrDefault(item => item.Id == id);
        if (record is null)
        {
            return;
        }

        _editingId = record.Id;
        SetRecordType(record.Type);
        SelectComboById<Category>(_categoryBox, record.CategoryId);
        LoadItemsForCategory();
        SelectComboById<FinanceItem>(_itemBox, record.ItemId);
        SelectComboById<Person>(_personBox, record.PersonId);
        _datePicker.Value = record.Date;
        _amountBox.Text = record.Amount.ToString("0.##");
        _noteBox.Text = record.Note;
    }

    private void SaveRecord()
    {
        if (_categoryBox.SelectedItem is not Category category || _itemBox.SelectedItem is not FinanceItem item || _personBox.SelectedItem is not Person person)
        {
            MessageBox.Show("请选择类别、项目和收支人。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return;
        }

        if (!decimal.TryParse(_amountBox.Text.Trim(), out var amount) || amount <= 0)
        {
            MessageBox.Show("请输入大于 0 的金额。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return;
        }

        var record = new TransactionRecord
        {
            Id = _editingId ?? 0,
            Type = _recordType,
            CategoryId = category.Id,
            ItemId = item.Id,
            PersonId = person.Id,
            Date = _datePicker.Value.Date,
            Amount = Math.Abs(amount),
            Note = _noteBox.Text.Trim()
        };

        if (_editingId is null)
        {
            _repository.AddTransaction(record);
        }
        else
        {
            _repository.UpdateTransaction(record);
        }

        ClearEditor();
        RefreshAll();
    }

    private void DeleteSelectedRecord()
    {
        if (_editingId is null)
        {
            MessageBox.Show("请先在表格中选择要删除的记录。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return;
        }

        if (MessageBox.Show("确定删除这条收支记录吗？", "确认删除", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        {
            return;
        }

        _repository.DeleteTransaction(_editingId.Value);
        ClearEditor();
        RefreshAll();
    }

    private void ClearEditor()
    {
        _editingId = null;
        _datePicker.Value = DateTime.Today;
        _amountBox.Clear();
        _noteBox.Clear();
        SetRecordType("收入");
        if (_personBox.Items.Count > 0)
        {
            _personBox.SelectedIndex = 0;
        }
    }

    private void OpenBasicData()
    {
        using var form = new BasicDataForm(_repository);
        form.ShowDialog(this);
        LoadLookups();
        RefreshAll();
    }

    private void OpenUserManagement()
    {
        using var form = new UserManagementForm(_repository);
        form.ShowDialog(this);
    }

    private void GridCellFormatting(object? sender, DataGridViewCellFormattingEventArgs e)
    {
        if (_grid.Columns[e.ColumnIndex].Name == "金额" && e.Value is string text)
        {
            e.CellStyle.ForeColor = text.StartsWith("+", StringComparison.Ordinal) ? Theme.Income : Theme.Expense;
        }
        else if (_grid.Columns[e.ColumnIndex].Name == "类型" && e.Value is string type)
        {
            e.CellStyle.ForeColor = type == "收入" ? Theme.Income : Theme.Expense;
        }
    }

    private static void SelectComboById<T>(ComboBox box, int id)
    {
        foreach (var item in box.Items)
        {
            var property = typeof(T).GetProperty("Id");
            if (property?.GetValue(item) is int itemId && itemId == id)
            {
                box.SelectedItem = item;
                return;
            }
        }
    }

    private static string Money(decimal value) => $"¥{value:N2}";
}
