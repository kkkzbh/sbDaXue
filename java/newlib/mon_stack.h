


#include<iostream>
#include<format>
#include<array>
#include<algorithm>
#include<iterator>
#include<ranges>

constexpr static int N{ 3000000 + 2 };

template<typename T>
struct stack
{
    std::array<T,N> a;
    int t{};
    void push(const T& i){ a[t++] = i; }
    void pop(){ --t; }
    bool empty(){ return !t; };
    int size(){ return t; }
    T& top(){ return a[t - 1]; }
};

std::array<int,N> a;
int n;
stack<int> stk;
std::array<int,N> f;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
    a[0] = std::numeric_limits<int>::max();
    stk.push(0);
    for(int i{ 1 }; i <= n; ++i)
    {
        for(int val{ stk.top() }; a[i] > a[val]; val = stk.top())
        {
            f[val] = i;
            stk.pop();
        }
        stk.push(i);
    }
    for(int i{ n }; i >= 1; --i)
    {
        if(f[i] == i)
        {
            f[i] = f[f[i]];
        }
    }
    std::ranges::copy(f | std::views::drop(1) | std::views::take(n),std::ostream_iterator<int>{ std::cout," " });

    return 0;
}