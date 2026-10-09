


#include<iostream>
#include<array>
#include<algorithm>

constexpr std::size_t size = (1 << 8) + 9;

struct node
{
    friend bool operator<(const node& n1,const node& n2){ return n1.power < n2.power; }
    auto operator<=>(const node& n) const = default;
    int index;
    int power;
};

inline std::size_t left(std::size_t i){ return 2 * i; }
inline std::size_t right(std::size_t i){ return 2 * i + 1; }

void solve(std::array<node,size>& a,std::size_t i)
{
    if(!a[left(i)].index) solve(a,left(i));
    if(!a[right(i)].index) solve(a,right(i));
    a[i] = std::max(a[left(i)],a[right(i)]);
}

int main()
{
    int n;
    std::cin >> n;
    std::array<node,size> a{};
    for(int i = (1 << n),ed = i + (1 << n);i != ed;++i)
    {
        a[i].index = i - ((1 << n) - 1);
        std::cin >> a[i].power;
    }
    solve(a,1);
    if(a[1] == a[2]) std::cout << a[3].index;
    else std::cout << a[2].index;

    return 0;
}