


#include<iostream>
#include<vector>
#include<algorithm>
#include<ranges>

std::vector<int> smallheap;
std::vector<int> bigheap;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    for(int i{ 1 },val; i <= n; ++i)
    {
        std::cin >> val;
        if(bigheap.empty() or val > bigheap.front())
        {
            smallheap.push_back(val);
            std::ranges::push_heap(smallheap,std::greater<>{});
        }
        else
        {
            bigheap.push_back(val);
            std::ranges::push_heap(bigheap);
        }
        int sz {(i + 1) >> 1 };
        while(bigheap.size() != sz)
        {
            if(bigheap.size() > sz)
            {
                smallheap.push_back(bigheap.front());
                std::ranges::push_heap(smallheap,std::greater<>{});
                std::ranges::pop_heap(bigheap);
                bigheap.pop_back();
            }
            else
            {
                bigheap.push_back(smallheap.front());
                std::ranges::push_heap(bigheap);
                std::ranges::pop_heap(smallheap,std::greater<>{});
                smallheap.pop_back();
            }
        }
        if(i & 1)
            std::cout << bigheap.front() << '\n';
    }

    return 0;
}