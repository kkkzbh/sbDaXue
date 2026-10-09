


#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<queue>
#include<array>
#include<ranges>

using int64 = long long;

constexpr int N{ 150000 + 2 };

struct node
{
    friend std::istream& operator>>(std::istream& is,node& n)
    {
        return is >> n.t1 >> n.t2;
    }
    int t1;
    int t2;
};

std::array<node,N> a;
int n;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin());
    std::ranges::sort(a | std::views::take(n),[](const node a,const node b){ return a.t2 < b.t2; });
    std::priority_queue<int,std::vector<int>,decltype([](const int a,const int b)
    {
        return a < b;
    })> que;
    int64 ans{};
    for(int64 i{},sum{}; i != n; ++i)
    {
        sum += a[i].t1;
        que.push(a[i].t1);
        if(sum > a[i].t2)
        {
            sum -= que.top();
            que.pop();
        }
        else
            ++ans;
    }
    std::cout << ans;

    return 0;
}