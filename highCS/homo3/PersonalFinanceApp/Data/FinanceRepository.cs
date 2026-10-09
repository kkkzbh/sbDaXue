using Microsoft.Data.Sqlite;
using PersonalFinanceApp.Models;

namespace PersonalFinanceApp.Data;

public sealed class FinanceRepository : IDisposable
{
    private readonly string _dbPath;
    private readonly SqliteConnection _connection;

    public FinanceRepository()
    {
        _dbPath = Path.Combine(AppContext.BaseDirectory, "finance.db");
        _connection = new SqliteConnection($"Data Source={_dbPath}");
        _connection.Open();
        ExecuteNonQuery("PRAGMA foreign_keys = ON;");
    }

    public string DatabasePath => _dbPath;

    public void Initialize()
    {
        ExecuteNonQuery("""
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT NOT NULL UNIQUE,
                password TEXT NOT NULL,
                display_name TEXT NOT NULL,
                role TEXT NOT NULL
            );
            CREATE TABLE IF NOT EXISTS categories (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                type TEXT NOT NULL,
                UNIQUE(name, type)
            );
            CREATE TABLE IF NOT EXISTS items (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                category_id INTEGER NOT NULL,
                name TEXT NOT NULL,
                type TEXT NOT NULL,
                FOREIGN KEY(category_id) REFERENCES categories(id),
                UNIQUE(category_id, name)
            );
            CREATE TABLE IF NOT EXISTS people (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL UNIQUE
            );
            CREATE TABLE IF NOT EXISTS transactions (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                type TEXT NOT NULL,
                category_id INTEGER NOT NULL,
                item_id INTEGER NOT NULL,
                person_id INTEGER NOT NULL,
                date TEXT NOT NULL,
                amount REAL NOT NULL,
                note TEXT NOT NULL,
                FOREIGN KEY(category_id) REFERENCES categories(id),
                FOREIGN KEY(item_id) REFERENCES items(id),
                FOREIGN KEY(person_id) REFERENCES people(id)
            );
            """);

        SeedDefaults();
    }

    public User? Authenticate(string username, string password)
    {
        using var command = CreateCommand("SELECT id, username, password, display_name, role FROM users WHERE username = $username AND password = $password LIMIT 1");
        command.Parameters.AddWithValue("$username", username);
        command.Parameters.AddWithValue("$password", password);
        using var reader = command.ExecuteReader();
        return reader.Read() ? ReadUser(reader) : null;
    }

    public List<User> GetUsers()
    {
        using var command = CreateCommand("SELECT id, username, password, display_name, role FROM users ORDER BY id");
        using var reader = command.ExecuteReader();
        var users = new List<User>();
        while (reader.Read())
        {
            users.Add(ReadUser(reader));
        }

        return users;
    }

    public void AddUser(string username, string password, string displayName, string role)
    {
        using var command = CreateCommand("INSERT INTO users(username, password, display_name, role) VALUES($username, $password, $displayName, $role)");
        command.Parameters.AddWithValue("$username", username);
        command.Parameters.AddWithValue("$password", password);
        command.Parameters.AddWithValue("$displayName", displayName);
        command.Parameters.AddWithValue("$role", role);
        command.ExecuteNonQuery();
    }

    public void UpdateUserPassword(int id, string password)
    {
        using var command = CreateCommand("UPDATE users SET password = $password WHERE id = $id");
        command.Parameters.AddWithValue("$id", id);
        command.Parameters.AddWithValue("$password", password);
        command.ExecuteNonQuery();
    }

    public void DeleteUser(int id)
    {
        using var command = CreateCommand("DELETE FROM users WHERE id = $id AND username <> 'admin'");
        command.Parameters.AddWithValue("$id", id);
        command.ExecuteNonQuery();
    }

    public List<Category> GetCategories(string? type = null)
    {
        using var command = CreateCommand(type is null
            ? "SELECT id, name, type FROM categories ORDER BY type, name"
            : "SELECT id, name, type FROM categories WHERE type = $type ORDER BY name");
        if (type is not null)
        {
            command.Parameters.AddWithValue("$type", type);
        }

        using var reader = command.ExecuteReader();
        var list = new List<Category>();
        while (reader.Read())
        {
            list.Add(new Category
            {
                Id = reader.GetInt32(0),
                Name = reader.GetString(1),
                Type = reader.GetString(2)
            });
        }

        return list;
    }

    public List<FinanceItem> GetItems(int? categoryId = null)
    {
        using var command = CreateCommand(categoryId is null
            ? "SELECT id, category_id, name, type FROM items ORDER BY type, name"
            : "SELECT id, category_id, name, type FROM items WHERE category_id = $categoryId ORDER BY name");
        if (categoryId is not null)
        {
            command.Parameters.AddWithValue("$categoryId", categoryId.Value);
        }

        using var reader = command.ExecuteReader();
        var list = new List<FinanceItem>();
        while (reader.Read())
        {
            list.Add(new FinanceItem
            {
                Id = reader.GetInt32(0),
                CategoryId = reader.GetInt32(1),
                Name = reader.GetString(2),
                Type = reader.GetString(3)
            });
        }

        return list;
    }

    public List<Person> GetPeople()
    {
        using var command = CreateCommand("SELECT id, name FROM people ORDER BY name");
        using var reader = command.ExecuteReader();
        var list = new List<Person>();
        while (reader.Read())
        {
            list.Add(new Person { Id = reader.GetInt32(0), Name = reader.GetString(1) });
        }

        return list;
    }

    public void AddCategory(string name, string type)
    {
        using var command = CreateCommand("INSERT OR IGNORE INTO categories(name, type) VALUES($name, $type)");
        command.Parameters.AddWithValue("$name", name);
        command.Parameters.AddWithValue("$type", type);
        command.ExecuteNonQuery();
    }

    public void AddItem(int categoryId, string name, string type)
    {
        using var command = CreateCommand("INSERT OR IGNORE INTO items(category_id, name, type) VALUES($categoryId, $name, $type)");
        command.Parameters.AddWithValue("$categoryId", categoryId);
        command.Parameters.AddWithValue("$name", name);
        command.Parameters.AddWithValue("$type", type);
        command.ExecuteNonQuery();
    }

    public void AddPerson(string name)
    {
        using var command = CreateCommand("INSERT OR IGNORE INTO people(name) VALUES($name)");
        command.Parameters.AddWithValue("$name", name);
        command.ExecuteNonQuery();
    }

    public void DeleteCategory(int id)
    {
        using var command = CreateCommand("DELETE FROM categories WHERE id = $id");
        command.Parameters.AddWithValue("$id", id);
        command.ExecuteNonQuery();
    }

    public void DeleteItem(int id)
    {
        using var command = CreateCommand("DELETE FROM items WHERE id = $id");
        command.Parameters.AddWithValue("$id", id);
        command.ExecuteNonQuery();
    }

    public void DeletePerson(int id)
    {
        using var command = CreateCommand("DELETE FROM people WHERE id = $id");
        command.Parameters.AddWithValue("$id", id);
        command.ExecuteNonQuery();
    }

    public List<TransactionRecord> GetTransactions(string filterType = "全部", bool onlyCurrentMonth = false, string search = "")
    {
        var sql = """
            SELECT t.id, t.type, t.category_id, c.name, t.item_id, i.name, t.person_id, p.name, t.date, t.amount, t.note
            FROM transactions t
            JOIN categories c ON c.id = t.category_id
            JOIN items i ON i.id = t.item_id
            JOIN people p ON p.id = t.person_id
            WHERE 1 = 1
            """;

        if (filterType is "收入" or "支出")
        {
            sql += " AND t.type = $type";
        }

        if (onlyCurrentMonth)
        {
            sql += " AND substr(t.date, 1, 7) = $month";
        }

        if (!string.IsNullOrWhiteSpace(search))
        {
            sql += " AND (c.name LIKE $search OR i.name LIKE $search OR p.name LIKE $search OR t.note LIKE $search)";
        }

        sql += " ORDER BY t.date DESC, t.id DESC";
        using var command = CreateCommand(sql);
        if (filterType is "收入" or "支出")
        {
            command.Parameters.AddWithValue("$type", filterType);
        }

        if (onlyCurrentMonth)
        {
            command.Parameters.AddWithValue("$month", DateTime.Today.ToString("yyyy-MM"));
        }

        if (!string.IsNullOrWhiteSpace(search))
        {
            command.Parameters.AddWithValue("$search", $"%{search.Trim()}%");
        }

        using var reader = command.ExecuteReader();
        var list = new List<TransactionRecord>();
        while (reader.Read())
        {
            list.Add(ReadTransaction(reader));
        }

        return list;
    }

    public FinanceSummary GetMonthlySummary()
    {
        using var command = CreateCommand("""
            SELECT type, SUM(amount), COUNT(*)
            FROM transactions
            WHERE substr(date, 1, 7) = $month
            GROUP BY type
            """);
        command.Parameters.AddWithValue("$month", DateTime.Today.ToString("yyyy-MM"));

        using var reader = command.ExecuteReader();
        var summary = new FinanceSummary();
        while (reader.Read())
        {
            var type = reader.GetString(0);
            var amount = reader.IsDBNull(1) ? 0 : Convert.ToDecimal(reader.GetValue(1));
            var count = reader.GetInt32(2);
            if (type == "收入")
            {
                summary.Income = amount;
            }
            else
            {
                summary.Expense = amount;
            }

            summary.Count += count;
        }

        return summary;
    }

    public void AddTransaction(TransactionRecord record)
    {
        using var command = CreateCommand("""
            INSERT INTO transactions(type, category_id, item_id, person_id, date, amount, note)
            VALUES($type, $categoryId, $itemId, $personId, $date, $amount, $note)
            """);
        BindTransaction(command, record);
        command.ExecuteNonQuery();
    }

    public void UpdateTransaction(TransactionRecord record)
    {
        using var command = CreateCommand("""
            UPDATE transactions
            SET type = $type, category_id = $categoryId, item_id = $itemId, person_id = $personId,
                date = $date, amount = $amount, note = $note
            WHERE id = $id
            """);
        command.Parameters.AddWithValue("$id", record.Id);
        BindTransaction(command, record);
        command.ExecuteNonQuery();
    }

    public void DeleteTransaction(int id)
    {
        using var command = CreateCommand("DELETE FROM transactions WHERE id = $id");
        command.Parameters.AddWithValue("$id", id);
        command.ExecuteNonQuery();
    }

    public void Dispose() => _connection.Dispose();

    private void SeedDefaults()
    {
        if (ScalarLong("SELECT COUNT(*) FROM users") == 0)
        {
            AddUser("admin", "123456", "张三", "admin");
        }

        if (ScalarLong("SELECT COUNT(*) FROM categories") == 0)
        {
            foreach (var name in new[] { "生活消费", "固定资产", "休闲娱乐", "医疗药品", "教育培训", "交通费", "其他支出" })
            {
                AddCategory(name, "支出");
            }

            foreach (var name in new[] { "工作收入", "投资收益", "其他收入" })
            {
                AddCategory(name, "收入");
            }
        }

        if (ScalarLong("SELECT COUNT(*) FROM people") == 0)
        {
            AddPerson("张三");
            AddPerson("李四");
        }

        if (ScalarLong("SELECT COUNT(*) FROM items") == 0)
        {
            var categories = GetCategories();
            AddDefaultItem(categories, "生活消费", "支出", "餐饮");
            AddDefaultItem(categories, "交通费", "支出", "地铁");
            AddDefaultItem(categories, "工作收入", "收入", "工资");
            AddDefaultItem(categories, "工作收入", "收入", "奖金");
            AddDefaultItem(categories, "投资收益", "收入", "基金");
            AddDefaultItem(categories, "投资收益", "收入", "股票");
        }

        if (ScalarLong("SELECT COUNT(*) FROM transactions") == 0)
        {
            var categories = GetCategories();
            var people = GetPeople();
            AddSeedTransaction(categories, people, "支出", "生活消费", "餐饮", "张三", DateTime.Today, 36, "午餐");
            AddSeedTransaction(categories, people, "收入", "工作收入", "工资", "张三", DateTime.Today.AddDays(-1), 8000, "月工资");
            AddSeedTransaction(categories, people, "支出", "交通费", "地铁", "李四", DateTime.Today.AddDays(-2), 7, "通勤");
            AddSeedTransaction(categories, people, "收入", "投资收益", "基金", "张三", DateTime.Today.AddDays(-3), 520, "收益");
        }
    }

    private void AddDefaultItem(List<Category> categories, string categoryName, string type, string itemName)
    {
        var category = categories.First(c => c.Name == categoryName && c.Type == type);
        AddItem(category.Id, itemName, type);
    }

    private void AddSeedTransaction(List<Category> categories, List<Person> people, string type, string categoryName, string itemName, string personName, DateTime date, decimal amount, string note)
    {
        var category = categories.First(c => c.Name == categoryName && c.Type == type);
        var item = GetItems(category.Id).First(i => i.Name == itemName);
        var person = people.First(p => p.Name == personName);
        AddTransaction(new TransactionRecord
        {
            Type = type,
            CategoryId = category.Id,
            ItemId = item.Id,
            PersonId = person.Id,
            Date = date,
            Amount = amount,
            Note = note
        });
    }

    private SqliteCommand CreateCommand(string sql)
    {
        var command = _connection.CreateCommand();
        command.CommandText = sql;
        return command;
    }

    private void ExecuteNonQuery(string sql)
    {
        using var command = CreateCommand(sql);
        command.ExecuteNonQuery();
    }

    private long ScalarLong(string sql)
    {
        using var command = CreateCommand(sql);
        return (long)(command.ExecuteScalar() ?? 0L);
    }

    private static User ReadUser(SqliteDataReader reader) => new()
    {
        Id = reader.GetInt32(0),
        Username = reader.GetString(1),
        Password = reader.GetString(2),
        DisplayName = reader.GetString(3),
        Role = reader.GetString(4)
    };

    private static TransactionRecord ReadTransaction(SqliteDataReader reader) => new()
    {
        Id = reader.GetInt32(0),
        Type = reader.GetString(1),
        CategoryId = reader.GetInt32(2),
        CategoryName = reader.GetString(3),
        ItemId = reader.GetInt32(4),
        ItemName = reader.GetString(5),
        PersonId = reader.GetInt32(6),
        PersonName = reader.GetString(7),
        Date = DateTime.Parse(reader.GetString(8)),
        Amount = Convert.ToDecimal(reader.GetValue(9)),
        Note = reader.GetString(10)
    };

    private static void BindTransaction(SqliteCommand command, TransactionRecord record)
    {
        command.Parameters.AddWithValue("$type", record.Type);
        command.Parameters.AddWithValue("$categoryId", record.CategoryId);
        command.Parameters.AddWithValue("$itemId", record.ItemId);
        command.Parameters.AddWithValue("$personId", record.PersonId);
        command.Parameters.AddWithValue("$date", record.Date.ToString("yyyy-MM-dd"));
        command.Parameters.AddWithValue("$amount", record.Amount);
        command.Parameters.AddWithValue("$note", record.Note);
    }
}
