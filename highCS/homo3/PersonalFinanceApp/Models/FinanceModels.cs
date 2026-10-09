namespace PersonalFinanceApp.Models;

public sealed class User
{
    public int Id { get; set; }
    public string Username { get; set; } = "";
    public string Password { get; set; } = "";
    public string DisplayName { get; set; } = "";
    public string Role { get; set; } = "user";
}

public sealed class Category
{
    public int Id { get; set; }
    public string Name { get; set; } = "";
    public string Type { get; set; } = "支出";

    public override string ToString() => Name;
}

public sealed class FinanceItem
{
    public int Id { get; set; }
    public int CategoryId { get; set; }
    public string Name { get; set; } = "";
    public string Type { get; set; } = "支出";

    public override string ToString() => Name;
}

public sealed class Person
{
    public int Id { get; set; }
    public string Name { get; set; } = "";

    public override string ToString() => Name;
}

public sealed class TransactionRecord
{
    public int Id { get; set; }
    public string Type { get; set; } = "支出";
    public int CategoryId { get; set; }
    public string CategoryName { get; set; } = "";
    public int ItemId { get; set; }
    public string ItemName { get; set; } = "";
    public int PersonId { get; set; }
    public string PersonName { get; set; } = "";
    public DateTime Date { get; set; } = DateTime.Today;
    public decimal Amount { get; set; }
    public string Note { get; set; } = "";
}

public sealed class FinanceSummary
{
    public decimal Income { get; set; }
    public decimal Expense { get; set; }
    public int Count { get; set; }
    public decimal Balance => Income - Expense;
}
