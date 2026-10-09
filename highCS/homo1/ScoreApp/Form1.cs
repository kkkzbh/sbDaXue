namespace ScoreApp;

public partial class Form1 : Form
{
    private readonly NumericUpDown[] _scoreInputs;

    public Form1()
    {
        InitializeComponent();

        _scoreInputs =
        [
            numJudge1, numJudge2, numJudge3, numJudge4, numJudge5,
            numJudge6, numJudge7, numJudge8, numJudge9, numJudge10
        ];
    }

    private void btnCalculate_Click(object sender, EventArgs e)
    {
        decimal[] scores = _scoreInputs.Select(input => input.Value).ToArray();

        decimal maxScore = scores.Max();
        decimal minScore = scores.Min();
        decimal finalScore = (scores.Sum() - maxScore - minScore) / (scores.Length - 2);

        lblHighestValue.Text = maxScore.ToString("0.##");
        lblLowestValue.Text = minScore.ToString("0.##");
        lblFinalValue.Text = finalScore.ToString("0.00");
    }

    private void btnReset_Click(object sender, EventArgs e)
    {
        foreach (NumericUpDown input in _scoreInputs)
        {
            input.Value = 1;
        }

        lblHighestValue.Text = "-";
        lblLowestValue.Text = "-";
        lblFinalValue.Text = "-";
        numJudge1.Focus();
    }
}
