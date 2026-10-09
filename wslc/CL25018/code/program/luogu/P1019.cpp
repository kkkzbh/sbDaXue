



#include<iostream>
#include<string>
#include<array>
#include<algorithm>

constexpr int size = 20 + 10;
constexpr std::size_t cei = 1ull << 63;

char st;
std::array<std::string,size> a;
int n;
std::array<std::array<std::size_t,size>,size> len;
std::array<int,size> vis;
std::string ans;
std::size_t max_length;

constexpr void initial()
{
    for(int i = 0; i != size;++i)
        for(int j = 0;j != size;++j)
            len[i][j] = cei;
}

constexpr std::size_t ml(int x,int y)
{
    std::size_t min_size = std::min(a[x].size(),a[y].size());
    std::size_t ret{cei};
    for(std::size_t sz = 1;sz != min_size && ret == cei;++sz)
        if(!a[x].compare(a[x].size() - sz,sz,a[y],0,sz)) ret = sz;
    return ret;
}

void dfs(int i)
{
    int m_index{};
    for(int _ = 1; _ <= n;++_) if(vis[_] != 2 && len[i][_] < len[i][m_index]) m_index = _;  //贪心剪枝 不过真的剪枝了吗？
    //答 : 剪了 每次第i个向其他的选择只有有限个 并且此贪心大概率最优解(每次选择重叠最小)
    if(!m_index)
    {
        max_length = std::max(max_length,ans.size());
        return;
    }
    for(int _ = 1;_ <= n;++_)
    {
        if(vis[_] != 2 && len[i][_] == len[i][m_index])
        {
            ans.append(a[_], len[i][_]); //a[_].size() - len[i][_]
            ++vis[_];
            dfs(_);
            --vis[_];
            ans.erase(ans.size() - a[_].size() + len[i][m_index],a[_].size() - len[i][m_index]);
        }
    }
}

int main()
{
    initial();
    std::cin >> n;
    for(int i = 1; i <= n;++i) std::cin >> a[i];
    for(int i = 1; i <= n;++i)
        for(int j = 1; j <= n;++j)
            len[i][j] = ml(i,j);
    std::cin >> st;
    int i;
    for(i = 1; i <= n;++i)
    {
        if(a[i][0] == st)
        {
            ++vis[i];
            ans += a[i];
            dfs(i);
            std::fill(vis.begin() + 1,vis.begin() + 1 + n,0);
            ans.clear();
        }
    }
    std::cout << max_length;

    return 0;
}
