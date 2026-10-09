

#include<iostream>
#include<array>

constexpr int N{ 500 + 2 };

std::array<std::array<int,N>,N> cake;
std::array<std::array<int,N>,N> prefix;
int r,c,a,b;

int sum(int x1,int y1,int x2,int y2)
{
    return prefix[x2][y2] - prefix[x2][y1 - 1] - prefix[x1 - 1][y2] + prefix[x1 - 1][y1 - 1];
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> r >> c >> a >> b;
    for(int i{ 1 }; i <= r; ++i)
        for(int j{ 1 }; j <= c; ++j)
        {
            std::cin >> cake[i][j];
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + cake[i][j];
        }
    int left{ 1 },right{ prefix[r][c] + 1 },cnt{ a * b };
    while(left != right)
    {
        int mid{ (left + right) >> 1 };
        int it{ 1 },cut{};
        int cntr{};
        while(it <= r && cntr != a)
        {
            int v{};
            int cntc{};
            for(int i{ 1 }; i <= c && cntc != b; ++i)
            {
                v += sum(cut + 1,i,it,i);
                if(v >= mid)
                {
                    ++cntc;
                    v = 0;
                }
            }
            if(cntc == b)
            {
                cut = it;
                ++cntr;
            }
            ++it;
        }
        if(cntr == a)
            left = mid + 1;
        else
            right = mid;
    }
    std::cout << left - 1;

    return 0;
}