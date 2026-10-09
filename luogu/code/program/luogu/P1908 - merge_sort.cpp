
#include<iostream>
#include<array>
#include<algorithm>
#include<iterator>

using int64 = long long;

constexpr static int N{ 500000 + 2 };

std::array<int,N> a;
std::array<int,N> buf;
int64 ans;
int n;

template<typename M_cmp>
void merge(int l,int mid,int r,M_cmp cmp)
{
    int start{ l };
    int m{ mid };
    int it{ l };
    while(l != mid and m != r)
    {
        if(cmp(a[m],a[l]))
        {
            buf[it++] = a[m++];
            ans += mid - l;
        }
        else
            buf[it++] = a[l++];
    }
    while(l != mid)
        buf[it++] = a[l++];
    while(m != r)
        buf[it++] = a[m++];
    for(; start != it; ++start)
        a[start] = buf[start];
}

template<typename M_cmp = std::less<>>
void merge_sort(int l,int r,M_cmp cmp = std::less<>{})
{
    if(l + 1 == r)
        return;
    int mid{ l + ((r - l) >> 1) };
    merge_sort(l,mid,cmp);
    merge_sort(mid,r,cmp);
    merge(l,mid,r,cmp);
}


int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin());
    merge_sort(0,n);
    std::cout << ans;

    return 0;
}