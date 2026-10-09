

#ifdef P1786

#include<iostream>
#include<string>
#include<array>
#include<algorithm>

#define DEBUG

constexpr int size = 110 + 10;
constexpr int post = 1 + 2 + 4 + 7 + 25 - 1;
constexpr int p = post + 100;
constexpr std::array<std::string,p> position{"","HuFa","HuFa","ZhangLao","ZhangLao","ZhangLao","ZhangLao",
                                                "TangZhu","TangZhu","TangZhu","TangZhu","TangZhu","TangZhu","TangZhu",
                                                "JingYing","JingYing","JingYing","JingYing","JingYing","JingYing","JingYing",
                                                "JingYing","JingYing","JingYing","JingYing","JingYing","JingYing","JingYing",
                                                "JingYing","JingYing","JingYing","JingYing","JingYing","JingYing","JingYing",
                                                "JingYing","JingYing","JingYing","JingYing"};
int pos = 0;
constexpr std::string BZ("BangZhong");
struct person
{
    std::string name;
    std::string post;
    int contribute = 0;
    int lv = 0;
};

int conver(const std::string& s)
{
    if(s == "BangZhu") return 999;
    if(s == "FuBangZhu") return 998;
    if(s == "HuFa") return 997;
    if(s == "ZhangLao") return 996;
    if(s == "TangZhu") return 995;
    if(s == "JingYing") return 994;
    return 993;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::array<person,size> a{};
    std::array<person*,size>pa{};
    int top = 0;
    for(int i = 1; i <= n;++i)
    {
        ++top;
        std::cin >> a[top].name >> a[top].post >> a[top].contribute >> a[top].lv;
    }
    for(int i = 1; i <= top;++i)
    {
        pa[i] = &a[i];
    }
    std::stable_sort(pa.begin() + 1,pa.begin() + top + 1,[](const person* p1,const person* p2) -> bool
    {
        return p1->contribute > p2->contribute;
    });
    int count = 0;
    for(int i = 1; i <= top;++i)
    {
        if(count != 3 && (pa[i]->post == "BangZhu" || pa[i]->post == "FuBangZhu"))
        {
            ++count;
        }
        else
        {
            pa[i]->post = pos == post ? BZ : position[++pos];
        }
    }
    std::stable_sort(a.begin() + 1,a.begin() + top + 1,[](const person& p1,const person& p2) -> bool
    {
        int a = conver(p1.post);
        int b = conver(p2.post);
        if(a != b) return a > b;
        return p1.lv > p2.lv;
    });
    for(int i = 1; i <= top;++i)
    {
        std::cout << a[i].name << ' ' << a[i].post << ' ' << a[i].lv << '\n';
    }
    return 0;
}

#endif
