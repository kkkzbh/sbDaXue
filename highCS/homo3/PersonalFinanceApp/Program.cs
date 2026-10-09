namespace PersonalFinanceApp;

static class Program
{
    [STAThread]
    static void Main()
    {
        ApplicationConfiguration.Initialize();
        using var repository = new Data.FinanceRepository();
        repository.Initialize();
        Application.Run(new Forms.LoginForm(repository));
    }
}
