

#include<iostream>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>

using int64 = long long;
using uint64 = unsigned long long;

constexpr int N{ 1000 + 2 };

#define push_heap(A) \
    heap.push_back(A);  \
    std::ranges::push_heap(heap);

#define pop_heap() \
    std::ranges::pop_heap(heap); \
    heap.pop_back();

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> v1,v2;
    v1.reserve(n);
    v2.reserve(n);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,std::back_insert_iterator{ v1 });
    std::copy_n(std::istream_iterator<int>{ std::cin },n,std::back_insert_iterator{ v2 });
    std::vector<int> heap;
    heap.reserve(2 * n);
    for(int i{}; i != n; ++i)
        heap.emplace_back(v1[0] + v2[i]);
    std::ranges::make_heap(heap);
    for(int i{ 1 }; i != n; ++i)
    {
        for(int j{}; j != n; ++j)
        {
            if(v1[i] + v2[j] >= heap[0])
                break;
            push_heap(v1[i] + v2[j]);
            while(heap.size() > n)
            {
                pop_heap();
            }
        }
    }
    std::ranges::sort_heap(heap);
    std::ranges::copy(heap,std::ostream_iterator<int>{ std::cout," " });

    return 0;
}