


#include<iostream>
#include<array>
#include<vector>
#include<bitset>

constexpr int N{ 500000 + 2 };
constexpr int null{};

std::array<int,N> a;
std::array<int,N> next;
std::array<int,N> to;
int top;
int n,root;
std::bitset<N> bit;

void insert(int x,int y)
{
    to[top] = y;
    next[top] = a[x];
    a[x] = top++;
}

int lca(int it,int x,int y)
{
    if(it == null or it == x or it == y)
    {
        return it;
    }
    std::vector<int> vec;
    bit.set(it);
    for(int i{ a[it] }; i != null; i = next[i])
    {
        if(!bit[to[i]])
        {
            int val{ lca(to[i], x, y) };
            if (val != null)
                vec.push_back(val);
        }
    }
    if(vec.size() == 1)
        return vec[0];
    else if(vec.size() == 2)
        return it;
    return null;
}

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int m;
    std::cin >> n >> m >> root;
    for(int i{ 1 },x,y; i != n; ++i)
    {
        std::cin >> x >> y;
        insert(x,y);
        insert(y,x);
    }
    for(int i{ 1 },x,y; i <= m; ++i)
    {
        std::cin >> x >> y;
        std::cout << lca(root,x,y) << '\n';
        bit.reset();
    }


    return 0;
}

