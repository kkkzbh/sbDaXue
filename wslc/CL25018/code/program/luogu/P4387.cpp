

#include<iostream>

constexpr std::size_t SZ = 100000 + 2;

template<typename T,std::size_t N>
struct array
{
    using size_type = std::size_t;
    using iterator = T*;
    T val[N];

    T& operator[](size_type i){ return val[i]; }
};

template<typename T,std::size_t N = 100000 + 2,typename Container = array<T,N>>
struct stack
{
    using size_type = size_t;
    Container C;
    size_type tp = 0;

    void push(const T& v){ C[tp++] = v; }
    void pop(){ --tp; }
    T& top(){ return C[tp - 1]; }
    bool empty(){ return !tp; }
    size_type size(){ return tp; }
    void clear(){ tp = 0; }
};

constexpr char ans[][5]{"No\n","Yes\n"};

int main()
{
    std::ios::sync_with_stdio(false),std::cout.tie(nullptr),std::cin.tie(nullptr);
    int q;
    std::cin >> q;
    stack<int> stk;
    array<int,SZ> pushed;
    array<int,SZ> poped;
    for(int i = 1,n;i <= q;++i)
    {
        std::cin >> n;
        for(int _ = 1; _ <= n;++_) std::cin >> pushed[_];
        for(int _ = 1; _ <= n;++_) std::cin >> poped[_];
        int it = 1,p = it;
        while(it <= n)
        {
            if(poped[it] == pushed[p]) ++it,++p;
            else if(!stk.empty() && stk.top() == poped[it]) ++it,stk.pop();
            else if(p <= n) stk.push(pushed[p++]);
            else break;
        }
        std::cout << ans[it > n];
        stk.clear();
    }

    return 0;
}