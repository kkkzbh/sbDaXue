

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

constexpr static uint64 prime{ 521ull };

template<typename T>
concept comparable = requires(T a,T b)
{
    { a < b } -> std::convertible_to<bool>;
};

template<typename T>
concept hashable = requires(T a)
{
    { std::hash<T>{}(a) } -> std::convertible_to<uint64>;
};

template<typename T>
concept contain_a = requires(T tree)
{
    tree.a;
};

template<typename T,typename U,typename Hash = std::hash<T>>
requires hashable<T>
struct map
{

private:

    struct M_iterator
    {
        using value_type = std::pair<T,U>;

        M_iterator() = default;

        M_iterator(value_type* M_ptr,uint64 ind,uint64 p,std::vector<std::vector<value_type>>& v)
                : ptr(M_ptr),index(ind),pos(p),vec(&v){}

        auto friend operator==(const M_iterator& i1,const M_iterator& i2) -> bool
        {
            return i1.ptr == i2.ptr;
        }

        auto operator*() -> value_type&
        {
            return *ptr;
        }

        auto operator*() const -> const value_type&
        {
            return *ptr;
        }

        auto operator->() -> value_type*
        {
            return ptr;
        }

        auto operator->() const -> const value_type*
        {
            return ptr;
        }

        auto operator++() -> M_iterator&
        {
            if(pos == (*vec)[index].size() - 1)
            {
                while(index != (*vec).size() - 1 and (*vec)[++index].empty()){}
                if(index == (*vec).size() - 1)
                {
                    ptr = nullptr;
                }
                else
                {
                    pos = 0;
                    ptr = &(*vec)[index][pos];
                }
            }
            else
            {
                ptr = &(*vec)[index][++pos];
            }
            return *this;
        }

        auto operator++(int) -> M_iterator
        {
            M_iterator ret{ *this };
            ++(*this);
            return ret;
        }

    private:

        std::vector<std::vector<value_type>>* vec;

        value_type* ptr{ nullptr };

        uint64 index;
        uint64 pos;

    };

public:

    constexpr static uint64 default_size{ 32 };
    constexpr static double loading{ 0.80 };

    using value_type = std::pair<T,U>;
    using iterator = M_iterator;

    //using const_iterator = const M_iterator;    // out of the time, realize for the time being.

    map() : sz(default_size)
    {
        vec.resize(default_size);
    }

    explicit map(uint64 cap) : sz(cap)
    {
        vec.resize(cap);
    }

    auto insert(const value_type& val) -> void
    {
        if(static_cast<double>(cnt) / vec.size() > loading)
        {
            rehash();
        }
        vec[conv(val.first)].push_back(val);
        ++cnt;
    }

    auto insert(value_type&& val) -> void
    {
        if(static_cast<double>(cnt) / vec.size() > loading)
        {
            rehash();
        }
        vec[conv(val.first)].push_back(std::move(val));
        ++cnt;
    }


    auto find(const T& key) -> iterator
    {
        uint64 it{ std::hash<T>{}(key) };
        return find(it,key);
    }

    auto find(uint64 it,const T& key) -> iterator
    {
        it %= sz;
        for(uint64 i{},cei{ vec[it].size() }; i != cei; ++i)
        {
            if(vec[it][i].first == key)
            {
                return iterator{ &vec[it][i],it,i,vec };
            }
        }
        return end();
    }

    auto operator[](const T& key) -> U&
    {
        uint64 it{ conv(key) };
        for(uint64 i{},cei{ vec[it].size() }; i != cei; ++i)
        {
            if(vec[it][i].first == key)
            {
                return vec[it][i].second;
            }
        }
        vec[it].emplace_back(key,U{});
        return vec[it].back().second;
    }

    auto operator[](T&& key) -> U&
    {
        uint64 it{ conv(key) };
        for(uint64 i{},cei{ vec[it].size() }; i != cei; ++i)
        {
            if(vec[it][i].first == key)
            {
                return vec[it][i].second;
            }
        }
        vec[it].emplace_back(std::move(key),U{});
        return vec[it].back().second;
    }

    auto begin() -> iterator
    {
        uint64 index{ -1ull };
        while(vec[++index].empty()){}
        return iterator{ &vec[index].front(),index,0,vec };
    }


    auto end() -> iterator
    {
        return iterator{};
    }


private:

    std::vector<std::vector<value_type>> vec;
    uint64 cnt{};
    uint64 sz{};

    auto conv(const T& val) const -> uint64
    {
        return std::hash<T>{}(val) % sz;
    }

    auto rehash() -> void
    {
        std::vector<std::vector<value_type>> buf(sz = (vec.size() << 1));
        for(auto&& v : vec)
        {
            for(auto&& val : v)
            {
                buf[conv(val.first)].push_back(std::move(val));
            }
        }
        vec = std::move(buf);
    }

};

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    let dfs = [map = map<int,int>{}](this auto& self,int n) {   // NOLINT
        if(n == 1) {
            return 1;
        }
        if(n == 2) {
            return 1;
        }
        if(n == 3) {
            return 1;
        }
        let it = map.find(n);
        if(it != map.end()) {
            return it->second;
        }
        let ssq = std::sqrt(n);
        let sq = int(ssq);

        let ret = 1;
        for(let i in iota(2,sq + 1) | filter([n](int i){ return not (n % i); })) {
            let _ = n / i;
            ret += self(_);
            ret += self(n / _);
        }
        if(sq == ssq) {
            ret -= self(n / sq);
        }

        return map[n] = ret;

    };

    std::cout << dfs(n) << '\n';

    return 0;
}


