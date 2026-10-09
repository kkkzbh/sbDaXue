

#include<iostream>
#include<array>
#include<algorithm>
#include<vector>

constexpr int M_size{ 300000 + 2 };


template<typename T>
struct hash;

template<typename T,typename M_hash = hash<T>>
struct unordered_set;

template<>
struct hash<int>
{
    std::size_t operator()(int val)
    {
        return val;
    }
};

template<typename T,typename M_hash>
struct unordered_set
{
    using iterator = typename std::vector<T>::const_iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    const static std::vector<T> vec;
    const static const_iterator npos;
    std::array<std::vector<T>,M_size> dis;
    const_iterator find(const T& v)
    {
        auto pos = M_hash()(v) % M_size;
        for(auto it = dis[pos].begin(); it != dis[pos].end();++it)
        {
            if(*it == v)
                return it;
        }
        return npos;
    }
    std::pair<const_iterator,bool> insert(const T& v)
    {
        auto pos = M_hash()(v) % M_size;
        for(auto it = dis[pos].begin(); it != dis[pos].end();++it)
        {
            if(*it == v)
                return std::make_pair(it,false);
        }
        dis[pos].push_back(v);
        return std::make_pair(dis[pos].end() - 1,true);
    }
    void clear()
    {
        for(auto&& i : dis)
        {
            i.clear();
        }
    }
};

template<typename T,typename M_hash>
const std::vector<T> unordered_set<T,M_hash>::vec;

template<typename T,typename M_hash>
const unordered_set<T,M_hash>::const_iterator unordered_set<T,M_hash>::npos = unordered_set<T,M_hash>::vec.end();

std::array<int,M_size> a;
unordered_set<int> set;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int T;
    std::cin >> T;
    while(T--)
    {
        int n;
        std::cin >> n;
        int top{};
        for(int i{},tmp; i != n;++i)
        {
            std::cin >> tmp;
            if(set.find(tmp) == unordered_set<int>::npos)
            {
                a[top++] = tmp;
                set.insert(tmp);
            }
        }
        for(int i{}; i != top;++i)
            std::cout << a[i] << ' ';
        std::cout << '\n';
        set.clear();
    }


    return 0;
}