


#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using size_t = std::size_t;

template<typename T>
struct node
{
    T val;
    size_t left = 0;
    size_t right = 0;
    size_t root = 0;
    node() = default;
    node(const T& v) : val(v){}

};

template<typename T>
struct tree
{
    using node = node<T>;
    constexpr static size_t buffer_size = 100 + 2;

    std::vector<node> a = decltype(a)(1);
    size_t root = 0;
    size_t t = 1;


    void insert(const T& v,size_t left,size_t right) noexcept
    {
        if(auto i = std::max(left,right); a.size() <= i)
            a.resize(i + 10);
        a[t].val = v;
        a[t].left = left;
        a[t].right = right;
        if(left) a[left].root = t;
        if(right) a[right].root = t;
        ++t;
    }
    size_t find_dis(size_t it) const noexcept
    {
        std::queue<size_t> que;
        std::vector<bool> vis(t + 1);
        que.push(it);
        vis[it] = true;
        size_t dis = 0;
        size_t level = 0;
        while(!que.empty())
        {
            for(size_t i = 0,end = que.size();i != end;++i)
            {
                size_t it = que.front();
                dis += level * a[it].val;
                if(a[it].root && !vis[a[it].root])
                { 
                    que.push(a[it].root);
                    vis[a[it].root] = true;
                }
                if(a[it].left && !vis[a[it].left])
                {
                    que.push(a[it].left);
                    vis[a[it].left] = true;
                }
                if(a[it].right && !vis[a[it].right])
                {
                    que.push(a[it].right);
                    vis[a[it].right] = true;
                }
                que.pop();
            }
            ++level;
        }
        return dis;
    }

    size_t size() const noexcept
    {
        return t;
    }

};

int main()
{
    freopen("../in","r",stdin);
    freopen("../out","w",stdout);
    tree<int> v;
    int n;
    std::cin >> n;
    for(int val,left,right; n; --n)
    {
        std::cin >> val >> left >> right;
        v.insert(val,left,right);
    }
    size_t ans = (1ull << 63);
    for(int i = 1; i != v.size();++i)
    {
        ans = std::min(ans,v.find_dis(i));
    }
    std::cout << ans;


    return 0;
}