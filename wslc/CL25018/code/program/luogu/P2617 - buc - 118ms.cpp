


#include<iostream>
#include<array>
#include<vector>

using uint64 = unsigned long long;

constexpr int N{ 100000 + 2 };
constexpr int MOD{ 10007 };

std::array<std::array<std::vector<int>,2>,N> a; //[color][奇偶] = //vec{ pair<id，val> }//  vec{ id }  //利用buc
std::array<int,N> buc;  //暂存 [id] = val

//注意到对于每一个数据项的计算公式为   id * ( (组个数n - 2) * val + prefix )
//本题还有 枚举 编号的方式计算 从而避免了使用vector动态存储每一组的各个id数据 (但需要存储每个id对应的color)
// 但显然使用上述 需要知道每一组的个数n(vec.size()) 以及在线求解存储每一组的 prefix存储 因为每一组的id是谁未知 无法最后离线求解

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    for(int i{ 1 }; i <= n; ++i)
        std::cin >> buc[i];
    for(int i{ 1 },color; i <= n; ++i)
    {
        std::cin >> color;
        a[color][i & 1].push_back(i);
    }
    uint64 ans{};
    for(int i{ 1 }; i <= m; ++i)    // i -> color   //枚举颜色
    {
        for(int j{}; j != 2; ++j)   //j -> 奇偶
        {
            uint64 prefix{};
            for(auto it : a[i][j])
                prefix += buc[it];
            for(auto it : a[i][j])
                ans = (ans + (it * ((a[i][j].size() - 2) * buc[it] + prefix))) % MOD;
        }
    }
    std::cout << ans;

    return 0;
}