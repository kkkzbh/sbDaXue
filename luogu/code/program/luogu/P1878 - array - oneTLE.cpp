


#include<iostream>
#include<array>
#include<algorithm>
#include<ranges>
#include<iterator>
#include<vector>
#include<utility>
#include<queue>
#include<cmath>

#define del(A) \
    a[A.first] - a[A.second]

constexpr int N{ 200000 + 2 };

std::array<char,N> ca;
std::array<int,N> a;
int n;
std::vector<std::pair<int,int>> vec;

auto cmp{ [](auto p1,auto p2)
          {
              if(int val{ std::abs(del(p1)) - std::abs(del(p2)) }; !val)
                  return p1.first > p2.first;
              else
                  return val > 0;
          }};

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    std::copy_n(std::istream_iterator<char>{ std::cin },n,ca.begin());
    int boycnt{ static_cast<int>(std::ranges::count_if(ca | std::views::take(n),[](char c){ return c == 'B'; }))};
    int girlcnt{ n - boycnt };
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin());
    std::vector<std::pair<int,int>> v;
    v.reserve(n);
    for(int i{}; i != n - 1; ++i)
        v.emplace_back(i,i + 1);
    std::priority_queue<std::pair<int,int>,
            std::vector<std::pair<int,int>>,decltype(cmp)> que{ cmp,std::move(v) };
    int k{};
    while(boycnt and girlcnt)
    {
        auto p{ que.top() };
        que.pop();
        if(ca[p.first] and ca[p.second] and ca[p.first] != ca[p.second])
        {
            ++k;
            ca[p.first] = ca[p.second] = 0;
            --boycnt;
            --girlcnt;
            vec.emplace_back(p.first,p.second);
            int l{ p.first - 1 },r{ p.second + 1 };
            while(l >= 0 and !ca[l])   //大循环 这次开销的O(n)用来找前驱 并没帮助到下次 其实帮到了
                --l;
            while(r < n and !ca[r])    //容易想到hack 退化O(n²)
                ++r;
            if(l >= 0 and r < n)
                que.emplace(l,r);
        }
    }
    std::cout << k << '\n';
    for(auto&& it : vec)
        std::cout << it.first + 1 << ' ' << it.second + 1 << '\n';  //prej

    return 0;
}