


#include<iostream>
#include<queue>
#include<vector>
#include<array>
#include<algorithm>
#include<iterator>

constexpr int N{ 200000 + 2 };

std::priority_queue<int> bigheap;
std::priority_queue<int,std::vector<int>,decltype([](const int a,const int b)
{
    return a > b;
})> smallheap;
int k;

void adj()
{
    while(bigheap.size() != k)
    {
        if(bigheap.size() > k)
        {
            smallheap.push(bigheap.top());
            bigheap.pop();
        }
        else
        {
            bigheap.push(smallheap.top());
            smallheap.pop();
        }
    }
}

void adj(int d)
{
    k += d;
    adj();
}

void insert(int i)
{
    if(bigheap.empty() or i > bigheap.top())
        smallheap.push(i);
    else
        bigheap.push(i);
    adj();  //可以压缩到else里减小常数 但是要保证插入前不改变k
}

int query()
{
    return bigheap.top();
}

std::array<int,N> add;
int n;
std::array<int,N> get;
int m;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> m;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,add.begin() + 1);
    std::copy_n(std::istream_iterator<int>{ std::cin },m,get.begin() + 1);
    for(int i{ 1 },it{ 1 }; i <= n; ++i)
    {
        insert(add[i]);
        while(get[it] == i)
        {
            ++k;
            ++it;
            adj();
            std::cout << query() << '\n';
        }
    }

    return 0;
}