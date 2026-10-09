

#include<iostream>
#include<array>

constexpr int N{ 1000 + 2 };

std::array<std::array<int,N>,N> diff;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n,m;
    std::cin >> n >> m;
    for(int i{},x1,x2,y1,y2; i != m; ++i)
    {
        std::cin >> x1 >> y1 >> x2 >> y2;
        diff[x1][y1] += 1;
        diff[x1][y2 + 1] -= 1;
        diff[x2 + 1][y1] -= 1;
        diff[x2 + 1][y2 + 1] += 1;
    }
    for(int i{ 1 }; i <= n; ++i)
    {
        for(int j{ 1 }; j <= n; ++j)
        {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            std::cout << diff[i][j] << ' ';
        }
        std::cout << '\n';
    }



    return 0;
}