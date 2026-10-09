

#include<iostream>
#include<queue>

std::priority_queue<int,std::vector<int>,
        decltype([](const int a,const int b)
        {
            return a < b;
        })> bigheap;

std::priority_queue<int,std::vector<int>,
        decltype([](const int a,const int b)
        {
            return a > b;
        })> smallheap;
int k;

void insert(int a)
{
    if(smallheap.empty() or a >= smallheap.top())   //写的有问题
        smallheap.push(a);
    else
        bigheap.push(a);
    while(smallheap.size() != k)
    {
        if(smallheap.size() > k)
        {
            bigheap.push(smallheap.top());
            smallheap.pop();
        }
        else
        {
            smallheap.push(bigheap.top());
            bigheap.pop();
        }
    }
}

int w;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n >> w;
    for(int i{ 1 },val; i <= n; ++i)
    {
        std::cin >> val;
        k = std::max(1,i * w / 100);
        insert(val);
        std::cout << smallheap.top() << ' ';
    }


    return 0;
}