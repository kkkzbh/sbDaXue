


#include<iostream>
#include<queue>
#include<vector>
#include<array>
#include<algorithm>
#include<iterator>
#include<utility>

using int64 = long long;
using uint64 = unsigned long long;

constexpr int N{ 100'000 + 2 };
constexpr int k_max{ 9 + 2 };

struct node
{
    friend std::istream& operator>>(std::istream& is,node& n)   //比较器 比较函数 投影函数 -> 灵活！
    {
        return is >> n.val;
    }
    friend bool operator<(node a,node b)
    {
        if(a.val == b.val)
            return a.heigh < b.heigh;
        return a.val < b.val;
    }
    friend bool operator>(node a,node b)
    {
        return !(a < b);
    }
    uint64 val;
    int heigh{};
};

int k;
int n;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> k;
    std::vector<node> a(n);
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin());
    int q{ (n - 1) % (k - 1) + 1 };
    std::priority_queue<node,std::vector<node>,std::greater<>> que{ std::greater<>(),std::move(a) };
    uint64 ans{};
    int heigh{};
    uint64 val{};
    if(q != 1)
    {
        for (int i{}; i != q; ++i)
        {
            node tmp = que.top();
            val += tmp.val;
            que.pop();
        }
        que.emplace(val, heigh + 1);
        ans += val;
        val = 0;
    }
    while(que.size() != 1)
    {
        for(int i{}; i != k; ++i)
        {
            node tmp = que.top();
            val += tmp.val;
            heigh = std::max(heigh,tmp.heigh);
            que.pop();
        }
        ans += val;
        que.emplace(val,heigh + 1);
        val = 0;
        heigh = 0;
    }
    std::cout << ans << '\n' << que.top().heigh;


    return 0;
}