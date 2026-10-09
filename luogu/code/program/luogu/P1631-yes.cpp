


#include<iostream>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<utility>

constexpr int N{ 100000 + 2 };

std::array<int,N> a;
std::array<int,N> b;
int n;

#define emplace_heap(...) \
    heap.emplace_back(__VA_ARGS__); \
    std::ranges::push_heap(heap,cmp)
#define pop_heap() \
    std::ranges::pop_heap(heap,cmp); \
    heap.pop_back()
#define val(P) \
    (a[P.first] + b[P.second])

auto cmp{ [](auto p1,auto p2)
          {
              return val(p1) > val(p2);
          }};

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin());
    std::copy_n(std::istream_iterator<int>{ std::cin },n,b.begin());
    std::vector<std::pair<int,int>> heap;
    for(int i{}; i != n; ++i)
        heap.emplace_back(i,0);
    std::ranges::make_heap(heap,cmp);
    for(int i{}; i != n; ++i)
    {
        auto p = heap[0];
        pop_heap();
        std::cout << val(p) << ' ';
        emplace_heap(p.first,p.second + 1);
    }


    return 0;
}