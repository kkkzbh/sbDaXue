

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>
#include<deque>

#define fun auto
template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    if constexpr(sizeof...(Args))
    {
        std::cout << std::vformat(fmts.get(), std::make_format_args(std::forward<Args>(args)...));
    }
    else
    {
        std::cout << fmts.get();
    }
}

constexpr static int N{ 100 + 2 };
constexpr static int N2{ 40000 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.v >> n.w >> n.m;
    }
    int v,w,m;
};

template<typename T,typename Cmp = std::less<>,typename Proj = std::identity>
struct monotonic_queue
{
    fun push(T it)
    {
        while(!que.empty() and Cmp{}(proj(it),proj(que.back())))
        {
            que.pop_back();
        }
        que.push_back(it);
    }

    fun pop(T it)
    {
        if(!que.empty() and que.front() == it)
        {
            que.pop_front();
        }
    }

    fun front()
    {
        return que.front();
    }

    fun back()
    {
        return que.back();
    }

    fun clear()
    {
        que.clear();
    }

    Proj proj;
    std::deque<T> que;

};

int n,w;
std::array<node,N> a;
std::array<int,N2> dp;

fun solve()
{
    std::cin >> n >> w;
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin() + 1);

    for(const auto [xv,xw,xm] : std::views::counted(a.begin() + 1,n))
    {
        auto proj = [=](const int j)
        {
            return dp[j] - (j / xw) * xv;
        };
        monotonic_queue<int,std::greater<>,decltype(proj)> que{ proj };
        for(int mod : std::views::iota(0,std::min(w + 1,xw)))
        {
            for(int j{ w - mod },cnt{ xm }; j >= 0 and cnt; j -= xw,--cnt)
            {
                que.push(j);
            }
            for(int j{ w - mod }; j >= xw; j -= xw)
            {
                if(int it{ j - xm * xw }; it >= 0)
                {
                    que.push(it);
                }
                dp[j] = proj(que.front()) + (j / xw) * xv;
                que.pop(j);
            }
            que.clear();
        }
    }

    print("{}",dp[w]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}