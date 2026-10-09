

#ifdef P1803

#include<iostream>
#include<array>
#include<algorithm>

constexpr int size = 1000000 + 10;

struct cmp
{
    int start = 0;
    int end = 0;
    cmp() = default;
    cmp(int st,int ed) : start(st),end(ed){}
};

std::array<cmp,size> cp;

int main()
{
    int n;
    std::cin >> n;
    for(int i = 1; i <=n ;++i)
    {
        std::cin >> cp[i].start >> cp[i].end;
    }
    std::sort(cp.begin() + 1,cp.begin() + 1 + n,[](const cmp& c1,const cmp& c2) -> bool
    {
       return c1.end < c2.end;
    });
    int count = 0;
    auto it = cp.begin();
    while((it = std::find_if(it + 1,cp.begin() + 1 + n,[&it](const cmp& c) -> bool
    {
        return c.start >= it->end;
    })) != cp.begin() + 1 + n)
    {
        ++count;
    }
    std::cout << count;

    return 0;
}

#endif
