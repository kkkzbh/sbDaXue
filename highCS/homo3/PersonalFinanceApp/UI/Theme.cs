namespace PersonalFinanceApp.UI;

public static class Theme
{
    public static readonly Color Background = Color.FromArgb(15, 20, 27);
    public static readonly Color Sidebar = Color.FromArgb(12, 17, 23);
    public static readonly Color Panel = Color.FromArgb(26, 32, 42);
    public static readonly Color PanelSoft = Color.FromArgb(32, 39, 50);
    public static readonly Color Border = Color.FromArgb(54, 63, 78);
    public static readonly Color Text = Color.FromArgb(235, 240, 246);
    public static readonly Color Muted = Color.FromArgb(147, 157, 172);
    public static readonly Color Accent = Color.FromArgb(38, 196, 171);
    public static readonly Color Income = Color.FromArgb(55, 210, 177);
    public static readonly Color Expense = Color.FromArgb(246, 111, 103);
    public static readonly Color Blue = Color.FromArgb(123, 157, 230);

    public static readonly Font TitleFont = new("Microsoft YaHei UI", 16F, FontStyle.Bold);
    public static readonly Font HeadingFont = new("Microsoft YaHei UI", 12F, FontStyle.Bold);
    public static readonly Font BodyFont = new("Microsoft YaHei UI", 10F);
    public static readonly Font SmallFont = new("Microsoft YaHei UI", 9F);

    public static Button Button(string text, Color? backColor = null)
    {
        var button = new Button
        {
            Text = text,
            BackColor = backColor ?? PanelSoft,
            ForeColor = Text,
            FlatStyle = FlatStyle.Flat,
            Font = BodyFont,
            Height = 42,
            Cursor = Cursors.Hand
        };
        button.FlatAppearance.BorderColor = Border;
        button.FlatAppearance.MouseOverBackColor = Color.FromArgb(42, 50, 63);
        return button;
    }

    public static Label Label(string text, Font? font = null, Color? color = null) => new()
    {
        Text = text,
        ForeColor = color ?? Text,
        Font = font ?? BodyFont,
        AutoSize = true
    };

    public static TextBox TextBox(string placeholder = "")
    {
        return new TextBox
        {
            PlaceholderText = placeholder,
            BackColor = PanelSoft,
            ForeColor = Text,
            BorderStyle = BorderStyle.FixedSingle,
            Font = BodyFont
        };
    }

    public static ComboBox ComboBox()
    {
        return new ComboBox
        {
            BackColor = PanelSoft,
            ForeColor = Text,
            FlatStyle = FlatStyle.Flat,
            DropDownStyle = ComboBoxStyle.DropDownList,
            Font = BodyFont
        };
    }

    public static void StyleGrid(DataGridView grid)
    {
        grid.BackgroundColor = Panel;
        grid.BorderStyle = BorderStyle.None;
        grid.EnableHeadersVisualStyles = false;
        grid.ColumnHeadersDefaultCellStyle.BackColor = Color.FromArgb(30, 37, 48);
        grid.ColumnHeadersDefaultCellStyle.ForeColor = Text;
        grid.ColumnHeadersDefaultCellStyle.Font = new Font(BodyFont, FontStyle.Bold);
        grid.ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle.Single;
        grid.DefaultCellStyle.BackColor = Panel;
        grid.DefaultCellStyle.ForeColor = Text;
        grid.DefaultCellStyle.SelectionBackColor = Color.FromArgb(42, 66, 68);
        grid.DefaultCellStyle.SelectionForeColor = Text;
        grid.AlternatingRowsDefaultCellStyle.BackColor = Color.FromArgb(22, 28, 37);
        grid.GridColor = Border;
        grid.RowHeadersVisible = false;
        grid.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
        grid.MultiSelect = false;
        grid.ReadOnly = true;
        grid.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
        grid.RowTemplate.Height = 42;
        grid.AllowUserToAddRows = false;
        grid.AllowUserToDeleteRows = false;
    }
}
