int[][] scores =
[
    new int[3],
    new int[4],
    new int[5]
];

Random random = new();
int total = 0;

Console.WriteLine("数组型数组的元素如下：");

for (int i = 0; i < scores.Length; i++)
{
    for (int j = 0; j < scores[i].Length; j++)
    {
        scores[i][j] = random.Next(30, 61);
        total += scores[i][j];
    }

    Console.WriteLine($"第{i + 1}个子数组: {string.Join(", ", scores[i])}");
}

Console.WriteLine($"所有元素之和: {total}");
