


#include<iostream>

constexpr std::size_t __Size = 32767 + 2;

template<typename T,std::size_t N>
struct array
{
    using size_type = std::size_t;
    using iterator = T*;
    T val[N];

    T& operator[](size_type i){ return val[i]; }
};

template<typename T1,typename T2>
auto min(const T1 e1,const T2 e2)
{
    if(e1 > e2) return e2;
    return e1;
}

template<typename T>
T abs(const T& v)
{
    if(v >= 0) return v;
    return -v;
}

#if 0

暴力 n//²
set维护有序序列 n个数 每次 插入log (二分查找两次log) 由于有序 利用插入位置可以直接得到相邻的数  nlog 由于STL二分不找到 返回end()
                    可以人为插入边界值 使得一定找到 有可能减少讨论
set就是平均下 nlogn 的动态有序序列 可以在每次处理的时候 都处理有序的数据
如果自己想到了一个 动态的有序处理情况 可以使用set维护 高级的数据结构 高级的效率 set不只是用来查数据 更是维护动态变化的有序序列
纯粹的查为 unordered_set


#endif

int main()
{
    std::ios::sync_with_stdio(false),std::cout.tie(nullptr),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    array<int,__Size> a;
    for(int i = 1; i <= n;++i) std::cin >> a[i];
    int sum{a[1]};
    for(int i = 2; i <= n;++i)
    {
        int m{~(1 << 31)};
        for(int j = i - 1; j >= 1;--j) m = min(m,abs(a[i] - a[j]));
        sum += m;
    }
    std::cout << sum;

    return 0;
}