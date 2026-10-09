


#include<iostream>
#include<array>
#include<string>
#include<cctype>
#include<utility>
#include<algorithm>
#include<cmath>

constexpr static int N{ 40 + 10 };
constexpr static double eps{ 1e-5 };
constexpr static char ans[][5]{ "N\n","Y\n" };

std::array<std::array<double,N>,N> a;
std::array<std::string,N> c;
int n,m;    // n 是列 m 是行

auto push(int cow,int v,std::string&& str) -> void
{
    int row{ 1 };
    while(!c[row].empty() and c[row] != str)
    {
        ++row;
    }
    c[row] = std::move(str);
    a[row][cow] = v;
    m = std::max(m,row);
}

auto swap(int l,int r) -> void //交换列
{
    if(l == r)
    {
        return;
    }
    for(int i{ 1 }; i <= m; ++i)
    {
        std::swap(a[i][l],a[i][r]);
    }
}

auto find(int row) -> int // 寻找该行 第一个不为零的列
{
    int it{ 1 };
    while(it <= n and std::abs(a[row][it]) < eps)
    {
        ++it;
    }
    return it > n ? row : it;
}

auto del(int row) -> void    // 削元  // 从第几行开始往下削 默认前n行削好
{
    swap(row,find(row)); // 交换 从row列开始交换
    for(int i{ row + 1 }; i <= m; ++i)  // 开削元
    {
        if(std::abs(a[i][row]) > eps)
        {
            double piv{}; // 系数
            if(std::abs(a[row][row]) > eps)
            {
                piv = a[i][row] / a[row][row];
            }
            for(int cow{ row }; cow <= n; ++cow)
            {
                a[i][cow] -= a[row][cow] * piv;
            }
        }
    }
}

auto cnt_zero() -> bool  // 暴力数秩
{
    int ret{};   // 默认秩
    for(int i{ 1 }; i <= m; ++i)    // 枚举行
    {
        for(int j{ 1 }; j <= n; ++j) // 枚举列
        {
            if(std::abs(a[i][j]) > eps)
            {
                ++ret;
                break;
            }
        }
    }
    return ret < n;
}

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int _;
    std::cin >> _;
    while(_--)
    {
        std::cin >> n;
        for (int i{ 1 }; i <= n; ++i)
        {
            std::string s, it;
            int num{};
            std::cin >> s;
            for (const auto ch: s)
            {
                if (isdigit(ch))
                {
                    num  = (num << 3) + (num << 1);
                    num += ch ^ 48;
                }
                else
                {
                    if (num)
                    {
                        push(i, num, std::move(it));
                        it.clear();
                        num = 0;
                    }
                    it.push_back(ch);
                }
            }
            if(num)
            {
                push(i,num,std::move(it));
                it.clear();
            }
        }
        for (int i{ 1 }; i <= m; ++i) // 按行削元
        {
            del(i);
        }
        std::cout << ans[cnt_zero()];
        for(int i{ 1 }; i <= m; ++i)    // 行
        {
            std::fill(a[i].begin() + 1,a[i].begin() + 1 + n + 1,0.0);   // 列
//            for(int j{ 1 }; j <= n; ++j)
//            {
//                a[i][j] = 0.0;
//            }
            c[i].clear();
        }
        m = 0;
    }

    return 0;
}