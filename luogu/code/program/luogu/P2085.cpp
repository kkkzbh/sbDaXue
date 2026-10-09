

#include<iostream>
#include<vector>
#include<algorithm>
#include<ranges>
#include<array>
#include<iterator>

constexpr int N{ 100'00 + 2 };

struct node
{
    friend std::istream& operator>>(std::istream& is,node& n)
    {
        return is >> n.a >> n.b >> n.c;
    }
    int a,b,c;
    [[nodiscard]]
    int cau(int i) const noexcept
    {
        return a * (i * i) + b * i + c;
    }
};

std::array<node,N> a;
int n;

std::vector<int> bigheap;
std::vector<int> smallheap;
int m;

#define push_small(A) \
    smallheap.push_back((A)); \
    std::ranges::push_heap(smallheap,std::greater<>{});

#define pop_small \
    std::ranges::pop_heap(smallheap,std::greater<>{}); \
    smallheap.pop_back();

#define push_big(A) \
    bigheap.push_back((A)); \
    std::ranges::push_heap(bigheap);

#define pop_big \
    std::ranges::pop_heap(bigheap); \
    bigheap.pop_back();

//一个优化方法 此做法还没完全优化 虽然复杂度是接近于完美的做法的 但也不太接近

// 注意观察 n个有序升序集合 每次需要取最小值 则可以动态开一个堆维护 每次取堆头 并动态的更新新入的集合的值 则是最优解

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> m;
    std::ranges::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin());
    for(int i{ 1 }; i <= m; ++i)
        bigheap.push_back(a[0].cau(i));
    std::ranges::make_heap(bigheap);
    for(int i{ 1 }; i != n; ++i)
    {
        int it{ 1 };
        int val{ a[i].cau(it++) };
        while(val < bigheap.front())
        {
            pop_big;
            push_big(val);
            val = a[i].cau(it++);
        }
    }
    std::ranges::sort_heap(bigheap);
    std::ranges::copy(bigheap,std::ostream_iterator<int>{ std::cout," " });


    return 0;
}