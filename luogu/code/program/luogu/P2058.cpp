

#include<iostream>


template<typename T>
struct queue
{
    constexpr static std::size_t SIZE = 3 * 1e5 + 2;
    T val[SIZE];
    std::size_t head{};
    std::size_t rear{};
    std::size_t sz{};

    void push(const T& v){ val[rear++] = v; rear %= SIZE; ++sz; }
    void pop(){ head = (head + 1) % SIZE; --sz; }
    T& front(){ return val[head]; }
    T& back(){ return val[rear - 1]; }
    bool empty(){ return !sz; }
};

template<typename T>
struct array
{
    constexpr static std::size_t SIZE = 1e5 + 2;
    T val[SIZE];

    T& operator[](std::size_t pos){ return val[pos]; }
};

template<typename T1,typename T2>
struct pair
{
    T1 time;
    T2 nation;

    pair() = default;
    pair(const T1& v1,const T2& v2) : time(v1),nation(v2){}
};

queue<pair<int,int>> que; // 时间 + 国籍  国籍 : nation
array<int> a;   // [index] = 国籍 a[index] = 人数

#if 0

其实本题的处理方法真的很常见 就是对一些特征数进行计数 然后每次操作依次更改这些数 更改后 我们能立马知道当前有多少个这个数
            然后一般会根据 是不是 大于 0 来改变什么状态 挺常见的做法
            总结 (冒号)  这个题目的k是有上限限制的 而跟n无关 时间复杂度也要多想想
能不能静态处理 (问号) 静态处理意味着需要先把状态保存下来 然后再处理

我觉得能 是可以的 静态建立队列 动态双指针处理时 再使用array

#endif

int main()
{
    ///freopen("../in.in","r",stdin);
    //freopen("../out.out","w",stdout);
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    int cnt{};
    for(int i = 1; i <= n;++i)  // n  -> n + 2k 线性
    {
        int time,k;
        std::cin >> time >> k;
        while(!que.empty() && time - que.front().time >= 86400)  //共k
        {
            if(!--a[que.front().nation]) --cnt;
            que.pop();
        }
        while(k--)  //共k
        {
            int nation;
            std::cin >> nation;
            if(!a[nation]) ++cnt;
            ++a[nation];
            que.push({time,nation});
        }
        std::cout << cnt << '\n';
    }

    return 0;
}